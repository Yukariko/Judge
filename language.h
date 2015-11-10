#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>

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
	char * const *getCompileCommand(const string& codePath);
	char * const *getRunCommand();

private:
	void initCommand();

	int langIdx;
	const char **compileCommand;
	const char **runCommand;
};

#endif