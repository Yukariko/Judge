#ifndef _JUDGE_H
#define _JUDGE_H

#include <iostream>
#include "language.h"

using namespace std;

class Judge
{
public:
	Judge(const string& lang, const string& codePath, const string& inPath, const string& outPath, const string& errPath, int timeLimit, int memoryLimit);
	bool compile();
	bool run();


private:
	Language lang;
	Execute exec;

	string codePath;
	string outPath;
	int timeLimit;
	int memoryLimit;
};

#endif