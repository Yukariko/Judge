#ifndef _C_H
#define _C_H

#include <iostream>
#include <vector>
#include <exception>
#include "log.h"
#include <sys/syscall.h>
#include "language.h"

class LanguageC : public Language
{
public:

    LanguageC()
    {
#ifdef __i386
        int LANG_CV[256]={85,8,SYS_time,SYS_read, SYS_uname, SYS_write, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_munmap, SYS_mprotect, SYS_mmap2, SYS_fstat64, SYS_set_thread_area, 252,0};
#else
        int LANG_CV[256] = {0,1,5,9,11,12,21,59,63,89,158,231, 8, SYS_time, SYS_read, SYS_uname, SYS_write, SYS_open,
				SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_munmap, SYS_mprotect,
				SYS_mmap, SYS_fstat, SYS_set_thread_area, 252, SYS_arch_prctl, 231, 0 };
#endif
        for(int i=0; LANG_CV[i]; i++)
            callCounter[(int)LANG_CV[i]] = true;
    }
    
    virtual char * const * getCompileCommand(const string& name)
    {
        try {
            char *codePath = new char[256];
            sprintf(codePath, "%s.c", name.c_str());
            return (char * const *)(new const char *[10] {"gcc", codePath, "-o", name.c_str(), "-std=c99", "-O2", "--static", "-Wall", "-lm", nullptr});
        } catch(exception e) {
            Log::terminate("LanguageC::getCompileCommand, " + string(e.what()));
        } 
    }

    virtual char * const * getJudgeCommand(const string& name, const vector<string>& args)
    {
        try {
            char *execPath = new char[name.length() + 3];
            sprintf(execPath, "./%s", name.c_str());

            char **cmd = new char *[2 + args.size()];
            
            cmd[0] = execPath;
            for(size_t i=0; i < args.size(); i++)
            {
                char *arg = new char[args[i].length() + 1];
                sprintf(arg, "%s", args[i].c_str());
                cmd[1 + i] = arg;
            }
            cmd[1 + args.size()] = nullptr;
            return (char * const *)cmd;
        } catch(exception e) {
            Log::terminate("LanguageC::getJudgeCommand" + string(e.what()));
        }
    }

private:
};

#endif