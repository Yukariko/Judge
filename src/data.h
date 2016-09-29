#ifndef _DATA_H
#define _DATA_H

#include <iostream>
#include <vector>

#include "result.h"

using namespace std;

class DataIterator
{
public:
    DataIterator(const DataIterator& iter) : data(iter.data), idx(iter.idx) {}
    DataIterator(Data *data) : data(data), idx(0) {}
    bool hasItem() const {return idx < data->getTestCaseNum();}
    void next() {idx++;}

    const string& getInput() const {return data->getInput(idx);}
    const string& getOutput() const {return data->getOutput(idx);}
    int getTimeLimit() const {return data->getTimeLimit();}
    int getMemoryLimit() const {return data->getMemoryLimit();}

    const vector<string>& getArgument() const { return {""}; }

    bool check(Result& result, const string& answer) const
    {
        if(result.getResult() != ResultId.ACCEPT)
            return false;
        
        return true;
    }

private:
    Data *data;
    int idx;
};

class Data
{
public:
    enum DataId {Normal, SpecialJudge};

    static Data* dataFactory(int probNo)
    {
        Configuration *conf = Configuration::getInstance();
        stringstream path(conf.getValue("dataPath"));
        path << probNo << "/config.txt";

        ifstream ifs(path.str());

        DataId dataId;
        ifs >> dataId;

        Data* data;

        switch(dataId)
        {
            case Normal: data = new Data(ifs); break;
            case SpecialJudge: data = new SpecialJudgeData(ifs); break;
            default: data = nullptr;
        }

        ifs.close();
        return data;
    }


    DataIterator getIterator() {return DataIterator(this);}
    int getTestCaseNum() {return testCaseNum;}

    const string& getInput(int idx)
    {
        if(idx < testCaseNum)
            return input[idx];
        return "";
    }

    const string& getOutput(int idx)
    {
        if(idx < testCaseNum)
            return output[idx];
        return "";
    }

    bool ready()
    {
        return true;
    }

protected:
    Data(ifstream& ifs)
    {
        ifs >> timeLimit >> memoryLimit;           
        ifs >> testCaseNum;

        input.resize(testCaseNum);
        output.resize(testCaseNum);
        for(int i=0; i < testCaseNum; i++)
            ifs >> input[i] >> output[i];
    }

private:
    vector<string> input, output;
    int timeLimit, memoryLimit, testCaseNum;
};

class SpecialJudgeData : Data
{

protected:
    SpecialJudgeData(ifstream& ifs) : Data(ifs)
    {
    }
};
#endif