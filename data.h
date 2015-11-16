#ifndef _DATA_H
#define _DATA_H

#include <iostream>
#include <vector>

using namespace std;

class Data
{
public:
	Data();

	void setDataPath(const string& dataPath);

	int getTestCaseNum() const;
	int getTimeLimit() const;
	int getMemoryLimit() const;
	const string& getSpecialJudgeLang() const;
	const string& getInputPath(int idx) const;
	const string& getOutputPath(int idx) const;

	bool isSpecialJudge() const;


private:
	void init();

	string dataPath;
	string specialJudgeLang;

	bool specialJudge;
	int testCaseNum;
	int timeLimit;
	int memoryLimit;

	vector<string> inputPaths;
	vector<string> outputPaths;
};

#endif