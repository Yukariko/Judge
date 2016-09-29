#include <sstream>
#include <exception>
#include "data.h"
#include "log.h"

Configuration* Configuration::instance;

DataIterator::DataIterator(const DataIterator& iter) : data(iter.data), idx(iter.idx) {}

DataIterator::DataIterator(Data *data) : data(data), idx(0) {}

bool DataIterator::hasItem() const
{
    return idx < data->getTestCaseNum();
}

void DataIterator::next()
{
    idx++;
}

const string& DataIterator::getInput() const
{
    return data->getInput(idx);
}

const string& DataIterator::getOutput() const
{
    return data->getOutput(idx);
}

int DataIterator::getTimeLimit() const
{
    return data->getTimeLimit();
}

int DataIterator::getMemoryLimit() const
{
    return data->getMemoryLimit();
}

const vector<string>& DataIterator::getArgument() const
{
    return {""};
}


bool DataIterator::check(Result& result, const string& answer) const
{
    if(result.getResult() != ACCEPT)
        return false;

    return true;
}



Data* Data::dataFactory(int probNo)
{
    try {
        Configuration *conf = Configuration::getInstance();

        stringstream path(conf->getValue("dataPath"));
        path << probNo << "/config.txt";
    
        ifstream ifs(path.str());

        int id;
        ifs >> id;
        DataId dataId = (DataId)id; 

        Data* data;

        switch(dataId)
        {
            case Normal: data = new Data(ifs); break;
            case SpecialJudge: data = new SpecialJudgeData(ifs); break;
            default: data = nullptr;
        }

        ifs.close();
        return data;
    } catch (exception e) {
        Log::terminate("Data::dataFactory " + path.str() + string(e.what()));
    }
}


DataIterator Data::getIterator() {return DataIterator(this);}
int Data::getTestCaseNum() {return testCaseNum;}

const string& Data::getInput(int idx)
{
    Log::terminate(idx >= testCaseNum, "Data::getInput");
    return input[idx];
}

const string& Data::getOutput(int idx)
{
    Log::terminate(idx >= testCaseNum, "Data::getOutput");
    return output[idx];
}

int Data::getTimeLimit()
{
    return timeLimit;
}

int Data::getMemoryLimit()
{
    return memoryLimit;
}

bool Data::ready()
{
    return true;
}

Data::Data(ifstream& ifs)
{
    try {
        ifs >> timeLimit >> memoryLimit;           
        ifs >> testCaseNum;

        input.resize(testCaseNum);
        output.resize(testCaseNum);
        for(int i=0; i < testCaseNum; i++)
            ifs >> input[i] >> output[i];
    } catch(exception e) {
        Log::terminate("Data::Data," + string(e.what()));
    }
}
