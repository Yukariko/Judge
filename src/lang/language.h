#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#include "data.h"
#include "result.h"
#include "c.h"

#include <assert.h>
#include <unistd.h>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

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
    static Language* languageFactory(LangId langId);
    virtual bool compile(const string& name);
    virtual Result judge(const string& name, const DataIterator& data);

protected:
    virtual char * const * getCompileCommand(const string& name) = 0;
    virtual char * const * getJudgeCommand(const string& name, const vector<string>& args) = 0;
    virtual int getCpuUsage(struct rusage& ruse) const;
    virtual int getMemoryUsage(int pid, struct rusage& ruse) const;
    virtual bool isSafeExit(int exitcode) const;
    bool callCounter[512] = {};
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