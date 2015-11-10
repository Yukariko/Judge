#ifndef _DATA_H
#define _DATA_H

#include <iostream>

using namespace std;

class Data
{
public:
	Data();

	void setDataPath(const string& dataPath);

	int getTestCaseNum() const;
	int getTimeLimit() const;
	int getMemoryLimit() const;
	const string& getInputPath(int idx) const;
	const string& getOutputPath(int idx) const;

private:
	void init();

	string dataPath;

	int testCaseNum;
	int timeLimit;
	int memoryLimit;

	vector<string> inputPaths;
	vector<string> outputPaths;
};

#endif