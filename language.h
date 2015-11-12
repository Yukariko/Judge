#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>
#include "okcalls.h"

using namespace std;

static const char *langs[] = {"C", "CPP", "CPP11", "JAVA", nullptr};
typedef enum {C,CPP,CPP11,JAVA} langCode;

class Language
{
public:
	Language();
	Language(const string& lang);
	Language(const Language& lang);
	~Language();
	char * const *getCompileCommand() const;
	char * const *getRunCommand() const;

	int getCpuUsage(struct rusage& ruse) const;
	int getMemoryUsage(int pid, struct rusage& ruse) const;
	bool isSafeExit(int exitcode) const;
	void initCallCounter(int *callCounter) const;


private:
	void initCommand();

	int langIdx;
	const char **compileCommand;
	const char **runCommand;
};

#endif