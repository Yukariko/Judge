#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>
#include "okcalls.h"
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

static const char *langs[] = {"C", "CPP", "CPP11", "JAVA", nullptr};
typedef enum {C,CPP,CPP11,JAVA} langCode;

class Language
{
public:
	Language();
	Language(const string& lang, const string& name);
	Language(const Language& lang);
	~Language();

	Language& operator= (const Language& lang);

	char * const *getCompileCommand() const;
	char * const *getRunCommand() const;

	int getCpuUsage(struct rusage& ruse) const;
	int getMemoryUsage(int pid, struct rusage& ruse) const;
	bool isSafeExit(int exitcode) const;
	void initCallCounter(int *callCounter) const;


private:
	void initCommand();

	string name;
	string codePath;
	string execPath;

	int langIdx;
	const char **compileCommand;
	const char **runCommand;
};

#endif