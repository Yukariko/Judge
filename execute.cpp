#include "execute.h"
#include <assert.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/resource.h>

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


int Execute::exec(char * const *cmd, int timeLimit, int memoryLimit)
{
	pid_t pid = fork();

	// child process
	if(pid == 0)
	{
		if(inputPath != "")
			assert(freopen(inputPath.c_str(), "r", stdin));
		if(outputPath != "")
			assert(freopen(outputPath.c_str(), "w", stdout));
		if(errorPath != "")
			assert(freopen(errorPath.c_str(), "a+", stderr));

		struct rlimit rlim;
		
		if(timeLimit != -1)
		{
			getrlimit(RLIMIT_CPU, &rlim);
			rlim.rlim_cur = timeLimit;
			setrlimit(RLIMIT_CPU, &rlim);
		}
		
		if(memoryLimit != -1)
		{
			getrlimit(RLIMIT_AS, &rlim);
			rlim.rlim_cur = memoryLimit * 1024 * 1024;
			setrlimit(RLIMIT_AS, &rlim);
		}
		//ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);

		execvp(cmd[0], cmd);
		exit(0);
	}

	// parent process
	else
	{
		int status = 0;
		struct rusage ruse;
		while(true)
		{
			wait4(pid, &status, 0, &ruse);

			// 정상 종료
			if(WIFEXITED(status))
			{
				cout << "complete" << endl;
				break;
			}

			int exitcode = WEXITSTATUS(status);

			// 비정상 종료
			if(exitcode != 0x05 && exitcode != 0)
			{
				cout << "not complete" << endl;
				break;
			}

			if(WIFSIGNALED(status))
			{
				cout << "signaled" << endl;
				break;
			}
		}

		cout << ruse.ru_utime.tv_sec << " " << ruse.ru_utime.tv_usec << ruse.ru_maxrss << endl;
		return status;
	}
}