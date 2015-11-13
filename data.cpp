#include "data.h"
#include <cstdio>
#include <assert.h>

Data::Data() : testCaseNum(0)
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

const string& Data::getSpecialJudgeLang(int idx) const
{
	return specialJudgeLang;
}

const string& Data::getInputPath(int idx) const
{
	return inputPaths[idx];
}

const string& Data::getOutputPath(int idx) const
{
	return outputPaths[idx];
}

bool Data::isSpecialJudge() const
{
	return specialJudge;
}

void Data::init()
{
	inputPaths.clear();
	outputPaths.clear();

	FILE *fp = fopen(dataPath.c_str(), "r");
	assert(fp != nullptr);

	assert(fscanf(fp, "%d", &testCaseNum) == 1);
	assert(fscanf(fp, "%d%d%d", &timeLimit, &memoryLimit, &specialJudge) == 3);

	if(specialJudge == true)
	{
		char buf[256];
		assert(fscanf(fp, "%s", buf) == 1);
		specialJudgeLang = buf;
	}

	for(int i=0; i < testCaseNum; i++)
	{
		char buf[256];
		assert(fscanf(fp, "%s", buf) == 1);
		inputPaths.push_back(buf);

		assert(fscanf(fp, "%s", buf) == 1);
		outputPaths.push_back(buf);
	}
}