#include "execute.h"

void Execute::setInPath(const string& inPath)
{
	this->inPath = inPath;
}
void Execute::setOutPath(const string& outPath)
{
	this->outPath = outPath;
}
void Execute::setErrPath(const string& errPath)
{
	this->errPath = errPath;
}


int Execute::exec(const char **cmd, int timeLimit, int memoryLimit)
{
	pid_t pid = fork();

	// child process
	if(pid == 0)
	{
		if(inPath != "")
			freopen(inPath.c_str(), stdin);
		if(outPath != "")
			freopen(outPath.c_str(), stdout);
		if(errPath != "")
			freopen(errPath.c_str(), stderr);

		execlv(cmd[0], cmd);
	}

	// parent process
	else
	{
		int status = 0;
		waitpid(pid, &status, 0);
		return status;
	}
}