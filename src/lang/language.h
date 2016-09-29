#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/resource.h>

#define FSIZE_LIMIT 64 * 1024 * 1024
#define STACK_LIMIT 64 * 1024 * 1024

#ifdef __i386
#define REG_SYSCALL orig_eax
#else
#define REG_SYSCALL orig_rax
#endif

enum LangId {C, CPP, JAVA};

class Language
{
public:
    static Language* languageFactory(LangId langId)
    {
        switch(langId)
        {
            case C: return new C();
            case CPP: return new Cpp();
            case JAVA: return new Java();
        }

        return nullptr;
    }

    virtual bool compile(const string& name)
    {
        int pid = fork();
        if(pid == 0)
        {
            assert(freopen("error.txt", "w", stderr));

            struct rlimit rlim;

            rlim.rlim_cur = 60;
            rlim.rlim_max = 60;
            setrlimit(RLIMIT_CPU, &rlim);
                    
            char * const * cmd = getCompileCommand(name);
            execvp(cmd[0], cmd);
            exit(0);
        }
        else
        {
            int status = 0;
            struct rusage ruse;
            wait4(pid, &status, 0, &ruse);
            return !status;
        }
    }

    virtual Result judge(const string& name, const DataIterator& data)
    {
        int timeLimit = data.getTimeLimit();
        int memoryLimit = data.getMemoryLimit() * 1024 * 1024;

        int pid = fork();
        // child process
        if(pid == 0)
        {
            if(data.getInput() != "")
                assert(freopen(data.getInput(), "r", stdin));
            assert(freopen("output.txt", "w", stdout));
            assert(freopen("error.txt", "w", stderr));

            struct rlimit rlim;
            rlim.rlim_cur = rlim.rlim_max = timeLimit;
            setrlimit(RLIMIT_CPU, &rlim);
            
            rlim.rlim_cur = rlim.rlim_max = STACK_LIMIT;
            setrlimit(RLIMIT_STACK, &rlim);

            rlim.rlim_cur = rlim.rlim_max = FSIZE_LIMIT;
            setrlimit(RLIMIT_FSIZE, &rlim);

            getrlimit(RLIMIT_AS, &rlim);
            rlim.rlim_cur = memoryLimit / 2 * 3;
            setrlimit(RLIMIT_AS, &rlim);
            
            char * const * cmd = getJudgeCommand(name, data.getArgument());
            ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
            execvp(cmd[0], cmd);
            exit(0);
        }

        // parent process
        else
        {
            int status = 0;
            struct rusage ruse;

            usedMemory = 0;
            while(true)
            {
                wait4(pid, &status, 0, &ruse);

                int curMemory = getMemoryUsage(pid, ruse);
                usedMemory = max(usedMemory, curMemory);

                if(usedMemory > memoryLimit)
                {
                    ptrace(PTRACE_KILL, pid, nullptr, nullptr);
                    return Result(ResultId.MEMORY_LIMIT_EXCEED);
                }

                // 정상 종료
                if(WIFEXITED(status))
                    break;

                int exitcode = WEXITSTATUS(status);

                // 비정상 종료
                if(isSafeExit(exitcode) == false)
                {
                    //printRuntimeError(strsignal(exitcode));
                    switch(exitcode) 
                    {
                        case SIGKILL:
                        case SIGXCPU:	return Result(ResultId.TIME_LIMIT_EXCEED);
                        case SIGXFSZ:	return Result(ResultId.OUTPUT_LIMIT_EXCEED);
                    }

                    return Result(ResultId.RUNTIME_ERROR);
                }

                // 시그널에 의한 종료
                if(WIFSIGNALED(status))
                {
                    int sig = WTERMSIG(status);
                    //printRuntimeError(strsignal(sig));
                    switch(sig) 
                    {
                        case SIGKILL:
                        case SIGXCPU:	return Result(ResultId.TIME_LIMIT_EXCEED);
                        case SIGXFSZ:	return Result(ResultId.OUTPUT_LIMIT_EXCEED);
                    }				
                    return Result(ResultId.RUNTIME_ERROR);
                }


                struct user_regs_struct reg;

                // check the system calls
                ptrace(PTRACE_GETREGS, pid, nullptr, &reg);

                if(!callCounter[reg.REG_SYSCALL])
                { //do not limit JVM syscall for using different JVM
                    ptrace(PTRACE_KILL, pid, nullptr, nullptr);
                    return Result(ResultId.RUNTIME_ERROR);
                }
                
                ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
            }

            usedTime = getCpuUsage(ruse);
            return Result(ResultId.ACCEPT, usedTime, usedMemory);
        }
    }


protected:
    virtual char * const * getCompileCommand(const string& name) = 0;
    virtual char * const * getJudgeCommand(const string& name, const string& args) = 0;

    virtual int getCpuUsage(struct rusage& ruse) const
    {
        int usedTime;
        usedTime = (ruse.ru_utime.tv_sec * 1000) + (ruse.ru_utime.tv_usec / 1000);
        usedTime += (ruse.ru_stime.tv_sec * 1000) + (ruse.ru_stime.tv_usec / 1000);
        return usedTime;
    }

    virtual int getMemoryUsage(int pid, struct rusage& ruse) const
    {
        char fn[4096], buf[4096];
        sprintf(fn, "/proc/%d/status", pid);

        FILE *pf = fopen(fn, "r");
        if(pf == nullptr)
            return 0;
        
        int m = strlen("VmPeak:	");

        int ret;
        while(fgets(buf, 4096 - 1, pf))
        {
            if(strncmp(buf, "VmPeak:	", m) == 0)
            {
                sscanf(buf + m + 1, "%d", &ret);
                break;
            }
        }
        fclose(pf);
        return ret * 1024;
    }

    virtual bool isSafeExit(int exitcode) const
    {
        if(exitcode == 0x05 || exitcode == 0)
            return true;
        return false;
    }

    vector<bool> callCounter(512, 0);
};

class C : public Language
{
public:



protected:
    C()
    {
        int LANG_CV[256]={85,8,SYS_time,SYS_read, SYS_uname, SYS_write, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_munmap, SYS_mprotect, SYS_mmap2, SYS_fstat64, SYS_set_thread_area, 252,0};
        for(int i=0; LANG_CV[i]; i++)
            callCounter[LANG_CV[i]] = true;
    }
    
    virtual char * const * getCompileCommand(const string& name)
    {
        char *codePath = new char[256];
        sprintf(codePath, "%s.c", name.c_str());
        string codePath = name + ".c";
        return (char * const *)(new const char *[] = {"gcc", codePath, "-o", name.c_str(), "-std=c99", "-O2", "--static", "-Wall", "-lm", nullptr});
    }

    virtual char * const * getJudgeCommand(const string& name, const vector<string>& args)
    {
        char *execPath = new char[name.length() + 3];
        sprintf(execPath, "./%s", name.c_str());

        const char **cmd = new const char *[2 + args.size()] = {execPath, nullptr};
        
        for(size_t i=0; i < args.size(); i++)
        {
            char *arg = new char[args[i].length() + 1];
            sprintf(argv, "%s", args[i].c_str());
            cmd[1 + i] = arg;
        }

        return (char * const *)cmd;
    }

private:
};


/*
class Cpp : public Language
{

};

class Java : public Language
{

protected:
    int getMemoryUsage(int pid, struct rusage& ruse) const
    {
		return ruse.ru_minflt * getpagesize();
    }
}
//*/
#endif