#include "data.h"
#include <cstdio>

Data::data() : testCaseNum(0)
{
}

void Data::setDataPath(const string& dataPath)
{
	this->dataPath = dataPath;
	init();
}

int Data::getTestCaseNum() const
{
	return testCaseNum;
}

int Data::getTimeLimit() const
{
	return timeLimit;
}

int Data::getMemoryLimit() const
{
	return memoryLimit;
}

const string& Data::getInputPath(int idx) const
{
	return inputPaths[idx];
}

const string& getOutputPath(int idx) const
{
	return outputPaths[idx];
}

void Data::init()
{
	testCasePaths.clear();

	FILE *fp = fopen(dataPath.c_str(), "r");

	fscanf(fp, "%d", &testCaseNum);
	fscanf(fp, "%d%d", &timeLimit, &memoryLimit);

	for(int i=0; i < testCaseNum; i++)
	{
		char buf[256];
		fscanf(fp, "%s", buf);
		inputPaths.push_back(buf);

		fscanf(fp, "%s", buf);
		outputPaths.push_back(buf);
	}
}