#ifndef _JUDGE_H
#define _JUDGE_H

#include <iostream>
#include "language.h"

using namespace std;

class Judge
{
public:
	Judge(Language& lang, const string& codePath, const string& inPath, const string& outPath);

private:
	Language lang;
	string codePath;
	string inPath;
	string outPath;
	string errorPath;
};

#endif