#include <exception>
#include "language.h"
#include "c.h"
#include "log.h"

Language* Language::languageFactory(LangId langId)
{
    switch(langId)
    {
        case C: return new LanguageC();
        //case CPP: return new Cpp();
        //case JAVA: return new Java();
    }

    return nullptr;
}

bool Language::compile(const string& name)
{
    int pid = fork();
    if(pid == 0)
    {
        Log::terminate(freopen("error.txt", "w", stderr), "Language::compile, error.txt");

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

Result Language::judge(const string& name, const DataIterator& data)
{
    int timeLimit = data.getTimeLimit();
    int memoryLimit = data.getMemoryLimit() * 1024 * 1024;

    int pid = fork();
    // child process
    if(pid == 0)
    {
        Log::terminate(freopen(data.getInput().c_str(), "r", stdin), "Language::judge, " + data.getInput());
        Log::terminate(freopen("output.txt", "w", stdout), "Language::judge, output.txt");
        Log::terminate(freopen("error.txt", "w", stderr), "Language::judge, error.txt");

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

        int usedMemory = 0;
        while(true)
        {
            wait4(pid, &status, 0, &ruse);

            int curMemory = getMemoryUsage(pid, ruse);
            usedMemory = max(usedMemory, curMemory);

            if(usedMemory > memoryLimit)
            {
                ptrace(PTRACE_KILL, pid, nullptr, nullptr);
                return Result(MEMORY_LIMIT_EXCEED);
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
                    case SIGXCPU:	return Result(TIME_LIMIT_EXCEED);
                    case SIGXFSZ:	return Result(OUTPUT_LIMIT_EXCEED);
                }

                return Result(RUNTIME_ERROR);
            }

            // 시그널에 의한 종료
            if(WIFSIGNALED(status))
            {
                int sig = WTERMSIG(status);
                //printRuntimeError(strsignal(sig));
                switch(sig) 
                {
                    case SIGKILL:
                    case SIGXCPU:	return Result(TIME_LIMIT_EXCEED);
                    case SIGXFSZ:	return Result(OUTPUT_LIMIT_EXCEED);
                }				
                return Result(RUNTIME_ERROR);
            }


            struct user_regs_struct reg;

            // check the system calls
            ptrace(PTRACE_GETREGS, pid, nullptr, &reg);

            if(!callCounter[reg.REG_SYSCALL])
            { //do not limit JVM syscall for using different JVM
                ptrace(PTRACE_KILL, pid, nullptr, nullptr);
                return Result(RUNTIME_ERROR);
            }
            
            ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
        }

        int usedTime = getCpuUsage(ruse);
        return Result(ACCEPT, usedTime, usedMemory);
    }
}

int Language::getCpuUsage(struct rusage& ruse) const
{
    int usedTime;
    usedTime = (ruse.ru_utime.tv_sec * 1000) + (ruse.ru_utime.tv_usec / 1000);
    usedTime += (ruse.ru_stime.tv_sec * 1000) + (ruse.ru_stime.tv_usec / 1000);
    return usedTime;
}

int Language::getMemoryUsage(int pid, struct rusage& ruse) const
{
    try {
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
    } catch(exception e) {
        Log::terminate("Language::getMemoryUsage, " + string(e.what()));
    }
    return 0;
}

bool Language::isSafeExit(int exitcode) const
{
    if(exitcode == 0x05 || exitcode == 0)
        return true;
    return false;
}
