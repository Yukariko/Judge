#ifndef _JUDGE_H
#define _JUDGE_H

#include <iostream>
#include "language.h"
#include "data.h"
#include "execute.h"

using namespace std;

class Judge
{
public:
	Judge(const string& lang, const string& codePath, const string& dataPath);
	bool compile();
	int run();
	bool check(const string& answerPath, const string& outputPath);

	void doJudge();
	void printResult();

private:
	Language lang;
	Execute exec;
	Data data;

	int resultAnswer;
	int resultTime;
	int resultMemory;
	string resultMessage;
};

#endif