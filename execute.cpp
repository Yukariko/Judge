#include "execute.h"
#include <assert.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <cstring>
#include <cstdio>
#include <algorithm>

Execute::Execute(const string& inputPath, const string& outputPath, const string& errorPath)
	: inputPath(inputPath), outputPath(outputPath), errorPath(errorPath)
{
}

void Execute::setInputPath(const string& inputPath)
{
	this->inputPath = inputPath;
}
void Execute::setOutputPath(const string& outputPath)
{
	this->outputPath = outputPath;
}
void Execute::setErrorPath(const string& errorPath)
{
	this->errorPath = errorPath;
}
void Execute::setLanguage(const string& lang)
{
	this->lang = Language(lang);
}

const string& Execute::getOutputPath() const
{
	return outputPath;
}
const string& Execute::getInputPath() const
{
	return inputPath;
}
const string& Execute::getErrorPath() const
{
	return errorPath;
}

void Execute::printRuntimeError(const char *msg)
{
	FILE *ferr = fopen(errorPath, "a+");
	fprintf(ferr, "Runtime Error:%s\n", msg);
	fclose(ferr);
}

int Execute::exec(bool isCompile, int timeLimit, int memoryLimit)
{
	memoryLimit *= 1024 * 1024;

	pid = fork();
	// child process
	if(pid == 0)
	{
		if(inputPath != "")
			assert(freopen(inputPath.c_str(), "r", stdin));
		if(outputPath != "")
			assert(freopen(outputPath.c_str(), "w", stdout));
		if(errorPath != "")
			assert(freopen(errorPath.c_str(), "w", stderr));

		struct rlimit rlim;
		
		getrlimit(RLIMIT_CPU, &rlim);
		rlim.rlim_cur = timeLimit;
		setrlimit(RLIMIT_CPU, &rlim);
		
		getrlimit(RLIMIT_AS, &rlim);
		rlim.rlim_cur = memoryLimit;
		setrlimit(RLIMIT_AS, &rlim);
		
		char * const * cmd;
		if(isCompile)
			cmd = lang.getCompileCommand();
		else
		{
			cmd = lang.getRunCommand();
			ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
		}

		execvp(cmd[0], cmd);
		exit(0);
	}

	// parent process
	else
	{
		int status = 0;
		struct rusage ruse;

		lang.initCallCounter(callCounter);

		usedMemory = 0;
		while(true)
		{
			wait4(pid, &status, 0, &ruse);

			if(isCompile)
			{
				return status;
			}

			int curMemory = lang.getMemoryUsage(ruse);
			usedMemory = max(usedMemory, curMemory);

			if(usedMemory > memoryLimit)
			{
				ptrace(PTRACE_KILL, pid, nullptr, nullptr);
				return MEMORY_LIMIT_EXCEED;
			}

			// 정상 종료
			if(WIFEXITED(status))
				break;

			int exitcode = WEXITSTATUS(status);

			// 비정상 종료
			if(lang.isSafeExit(exitcode) == false)
			{
				printRuntimeError(strsignal(exitcode));
				switch(exitcode) 
				{
					case SIGKILL:
					case SIGXCPU:	return TIME_LIMIT_EXCEED;
					case SIGXFSZ:	return OUTPUT_LIMIT_EXCEED;
				}				
				return RUNTIME_ERROR;
			}

			// 시그널에 의한 종료
			if(WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				printRuntimeError(strsignal(sig));
				switch(sig) 
				{
					case SIGKILL:
					case SIGXCPU:	return TIME_LIMIT_EXCEED;
					case SIGXFSZ:	return OUTPUT_LIMIT_EXCEED;
				}				
				return RUNTIME_ERROR;
			}


			struct user_regs_struct reg;

			// check the system calls
			ptrace(PTRACE_GETREGS, pid, nullptr, &reg);

			if(!callCounter[reg.REG_SYSCALL])
			{ //do not limit JVM syscall for using different JVM
				char error[4096];
				sprintf(error,"[ERROR] A Not allowed system callid:%ld\n",(long)reg.REG_SYSCALL);
				printRuntimeError(error);
				ptrace(PTRACE_KILL, pid, nullptr, nullptr);
				return RUNTIME_ERROR;
			}
			
			ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
		}

		usedTime = lang.getCpuUsage(ruse);
		return status;
	}
}