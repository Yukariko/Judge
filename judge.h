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
	Judge(const string& lang, const string& dataPath);
	
	int check(const string& answerPath, const string& outputPath);
	int check(const string& spjPath);

	void doJudge();
	void printResult();

	static void rtrim(char *str, int& len);

private:
	Language lang;
	Execute exec;
	Execute spjExec;
	Data data;

	int resultAnswer;
	int resultTime;
	int resultMemory;
	string resultMessage;
};

#endif