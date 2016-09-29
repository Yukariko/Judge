#include "data.h"

DataIterator::DataIterator(const DataIterator& iter) : data(iter.data), idx(iter.idx) {}
DataIterator::DataIterator(Data *data) : data(data), idx(0) {}
bool DataIterator::hasItem() const {return idx < data->getTestCaseNum();}
void DataIterator::next() {idx++;}

const string& DataIterator::getInput() const {return data->getInput(idx);}
const string& DataIterator::getOutput() const {return data->getOutput(idx);}
int DataIterator::getTimeLimit() const {return data->getTimeLimit();}
int DataIterator::getMemoryLimit() const {return data->getMemoryLimit();}

const vector<string>& DataIterator::getArgument() const { return {""}; }

bool DataIterator::check(Result& result, const string& answer) const
{
if(result.getResult() != ResultId.ACCEPT)
    return false;

return true;
}



Data* Data::dataFactory(int probNo)
{
    Configuration *conf = Configuration::getInstance();
    stringstream path(conf.getValue("dataPath"));
    path << probNo << "/config.txt";

    ofstream ofs(path.str());

    DataId dataId;
    ofs >> dataId;

    Data* data;

    switch(dataId)
    {
        case Normal: data = new Data(ofs); break;
        case SpecialJudge: data = new SpecialJudgeData(ofs); break;
        default: data = nullptr;
    }

    ofs.close();
    return data;
}


DataIterator Data::getIterator() {return DataIterator(this);}
int Data::getTestCaseNum() {return testCaseNum;}

const string& Data::getInput(int idx)
{
    if(idx < testCaseNum)
        return input[idx];
    return "";
}

const string& Data::getOutput(int idx)
{
    if(idx < testCaseNum)
        return output[idx];
    return "";
}

bool Data::ready()
{
    return true;
}

Data::Data(ofstream& ofs)
{
    ofs >> timeLimit >> memoryLimit;           
    ofs >> testCaseNum;

    input.resize(testCaseNum);
    output.resize(testCaseNum);
    for(int i=0; i < testCaseNum; i++)
        ofs >> input[i] >> output[i];
}
