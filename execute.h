#ifndef _EXECUTE_H
#define _EXECUTE_H

#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

using namespace std;

class Execute
{
public:
	Execute(const string& inPath = "", const string& outPath = "", const string& errPath = "");
	int exec(const char **cmd, int timeLimit = -1, int memoryLimit = -1);

	void setInPath(const string& inPath);
	void setOutPath(const string& outPath);
	void setErrPath(const string& errPath);

private:
	string inPath;
	string outPath;
	string errPath;
};

#endif