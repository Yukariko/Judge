#ifndef _DATA_H
#define _DATA_H

class Data
{
public:
    Data(int probNo);

private:
    vector<string> inputs;
    vector<string> outputs;
    int timeLimit, memoryLimit;

};

#endif