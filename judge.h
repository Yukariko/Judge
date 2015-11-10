#ifndef _JUDGE_H
#define _JUDGE_H

#include <iostream>
#include "language.h"
#include "data.h"
#include "execute.h"

using namespace std;

typedef enum {ACCEPT, WRONG_ANSWER, COMPILE_ERROR, RUN_TIME_ERROR, TIME_LIMIT_EXCEED, MEMORY_LIMIT_EXCEED} result;

class Judge
{
public:
	Judge(const string& lang, const string& codePath, const string& dataPath);
	bool compile();
	int run();
	bool check(const string& answerPath, const string& outputPath);

	int doJudge();

private:
	Language lang;
	Execute exec;
	Data data;

	string codePath;
};

#endif