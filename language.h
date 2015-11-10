#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include <iostream>

using namespace std;

const char *langs[] = {"C", "CPP", "CPP11", "JAVA", nullptr};
typedef enum {C,CPP,CPP11,JAVA} langCode;

class Language
{
public:
	Language(const string& lang);
	~Language();
	const char ** getCompileCommand(const string& codePath);

private:
	int langIdx;
	const char **cmd;
};

#endif