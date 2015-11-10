#include "language.h"

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

	switch(langIdx)
	{
	case C:
		cmd = new const char *[7] {"gcc", "-o", "test", "-std=c99", "-O2", nullptr, nullptr};
		break;
	case CPP:
		cmd = new const char *[6] {"g++", "-o", "test", "-O2", nullptr, nullptr};
		break;
	case CPP11:
		cmd = new const char *[7] {"g++", "-o", "test", "-std=c++11", "-O2", nullptr, nullptr};
		break;
	case JAVA:
		break;
	}
}

Language::~Language() 
{
	if(cmd)
		delete[] cmd;
}

const char ** Language::getCompileCommand(const string& codePath)
{
	switch(langIdx)
	{
	case C:
		cmd[5] = codePath.c_str();
		break;
	case CPP:
		cmd[4] = codePath.c_str();
		break;
	case CPP11:
		cmd[5] = codePath.c_str();
		break;
	case JAVA:
		break;
	}
	return cmd;
}