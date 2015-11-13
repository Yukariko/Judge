#ifndef _EXECUTE_H
#define _EXECUTE_H

#include <iostream>
#include "language.h"

using namespace std;

typedef enum {ACCEPT, WRONG_ANSWER, COMPILE_ERROR, RUNTIME_ERROR, TIME_LIMIT_EXCEED, MEMORY_LIMIT_EXCEED, OUTPUT_LIMIT_EXCEED, OUTPUT_FORMAT_WRONG} result;

#define FSIZE_LIMIT 64 * 1024 * 1024
#define STACK_LIMIT 64 * 1024 * 1024

#ifdef __i386
#define REG_SYSCALL orig_eax
#else
#define REG_SYSCALL orig_rax
#endif


class Execute
{
public:
	Execute(const string& inputPath = "", const string& outputPath = "", const string& errorPath = "");
	int exec(bool isCompile, int timeLimit = 60, int memoryLimit = 128);

	void setInputPath(const string& inputPath);
	void setOutputPath(const string& outputPath);
	void setErrorPath(const string& errorPath);
	void setLanguage(const string& lang);

	const string& getOutputPath() const;
	const string& getInputPath() const;
	const string& getErrorPath() const;

	int getUsedTime() const;
	int getUsedMemory() const;

private:
	void printRuntimeError(const char *msg);

	string inputPath;
	string outputPath;
	string errorPath;

	Language lang;

	int pid;
	int usedTime;
	int usedMemory;

	int callCounter[512];
};

#endif