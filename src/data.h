#ifndef _DATA_H
#define _DATA_H

#include <iostream>
#include <vector>

#include "result.h"

using namespace std;

class Data;

class DataIterator
{
public:
    DataIterator(const DataIterator& iter);
    DataIterator(Data *data);
    bool hasItem() const;
    void next();

    const string& getInput() const;
    const string& getOutput() const;
    int getTimeLimit() const;
    int getMemoryLimit() const;

    const vector<string>& getArgument() const;

    bool check(Result& result, const string& answer) const;
private:
    Data *data;
    int idx;
};

class Data
{
public:
    enum DataId {Normal, SpecialJudge};

    static Data* dataFactory(int probNo);
    DataIterator getIterator();
    int getTestCaseNum();

    const string& getInput(int idx);
    const string& getOutput(int idx);
    bool ready();

protected:
    Data(ofstream& ofs);

private:
    vector<string> input, output;
    int timeLimit, memoryLimit, testCaseNum;
};

class SpecialJudgeData : Data
{

protected:
    SpecialJudgeData(ofstream& ofs) : Data(ofs)
    {
    }
};
#endif