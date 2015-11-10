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
	Execute(const string& inputPath = "", const string& outputPath = "", const string& errorPath = "");
	int exec(char * const *cmd, int timeLimit = -1, int memoryLimit = -1);

	void setInputPath(const string& inputPath);
	void setOutputPath(const string& outputPath);
	void setErrorPath(const string& errorPath);

	const string& getOutputPath() const;
	const string& getInputPath() const;
	const string& getErrorPath() const;

private:
	string inputPath;
	string outputPath;
	string errorPath;
};

#endif