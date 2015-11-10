#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>

using namespace std;

const char *langs[] = {"C", "CPP", "CPP11", "JAVA", nullptr};
typedef enum {C,CPP,CPP11,JAVA} langCode;

class Language
{
public:
	Language();
	Language(const string& lang);
	Language(const Language& lang);
	~Language();
	const char * const *getCompileCommand(const string& codePath);
	const char * const *getRunCommand();

private:
	void initCommand();

	int langIdx;
	const char * const *compileCommand;
	const char * const *runCommand;
};

#endif