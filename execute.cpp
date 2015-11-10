#include "execute.h"

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


int Execute::exec(const char **cmd, int timeLimit, int memoryLimit)
{
	pid_t pid = fork();

	// child process
	if(pid == 0)
	{
		if(inputPath != "")
			freopen(inputPath.c_str(), "r", stdin);
		if(outputPath != "")
			freopen(outputPath.c_str(), "w", stdout);
		if(errorPath != "")
			freopen(errorPath.c_str(), "a+", stderr);

		execv(cmd[0], cmd);
		return -1;
	}

	// parent process
	else
	{
		int status = 0;
		waitpid(pid, &status, 0);
		return status;
	}
}