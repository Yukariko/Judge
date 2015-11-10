#include "language.h"

Language::Language() : langIdx(-1), compileCommand(nullptr), runCommand(nullptr) {}

Language::Language(const string& lang)
{
	langIdx = 0;
	while(langs[langIdx] != nullptr && lang != langs[langIdx])
		langIdx++;

	if(langs[langIdx] == nullptr)
	{
		cerr << "Invalid Language" << endl;
		exit(1);
	}

	initCommand();
}

Language::Language(const Language& lang) : langIdx(lang.langIdx)
{
	initCommand();
}

Language::~Language() 
{
	if(compileCommand)
		delete[] compileCommand;

	if(runCommand)
		delete[] runCommand;
}


void Language::initCommand()
{
	if(compileCommand)
		delete[] compileCommand;

	if(runCommand)
		delete[] runCommand;

	switch(langIdx)
	{
	case C:
		compileCommand = new const char *[7] {"gcc", "-o", "test", "-std=c99", "-O2", nullptr, nullptr};
		runCommand = new const char *[3] {"test", "test", nullptr};
		break;
	case CPP:
		compileCommand = new const char *[6] {"g++", "-o", "test", "-O2", nullptr, nullptr};
		runCommand = new const char *[3] {"test", "test", nullptr};
		break;
	case CPP11:
		compileCommand = new const char *[7] {"g++", "-o", "test", "-std=c++11", "-O2", nullptr, nullptr};
		runCommand = new const char *[3] {"test", "test", nullptr};
		break;
	case JAVA:
		break;
	}
}

char * const *Language::getCompileCommand(const string& codePath)
{
	char buf[256];
	strcpy(buf, codePath.c_str());
	switch(langIdx)
	{
	case C:
		compileCommand[5] = codePath.c_str();
		break;
	case CPP:
		compileCommand[4] = codePath.c_str();
		break;
	case CPP11:
		compileCommand[5] = codePath.c_str();
		break;
	case JAVA:
		break;
	}
	return (char * const *)compileCommand;
}

char * const *Language::getRunCommand()
{
	return (char * const *)runCommand;
}
