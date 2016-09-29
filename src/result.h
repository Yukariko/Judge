#ifndef _RESULT_H
#define _RESULT_H

#include <iostream>
#include <algorithm>

using namespace std;

enum ResultId {
    EMPTY, NO_RESULT, READY, RUNNING, ACCEPT, WRONG_ANSWER, COMPILE_ERROR,
    RUNTIME_ERROR, TIME_LIMIT_EXCEED, MEMORY_LIMIT_EXCEED, OUTPUT_LIMIT_EXCEED,
    OUTPUT_FORMAT_WRONG, OJ_MISS
};


class Result
{
public:
    
    Result(ResultId resultId, int time = -1, int memory = -1) : _resultId(resultId),
        _time(time), _memory(memory) {}

    Result(const Result& result) : _resultId(result._resultId),
        _time(result._time), _memory(result._memory) {}

    ResultId getResult() const { return _resultId; }

    int getTime() const { return _time; }
    int getMemory() const { return _memory; }


    void setMax(const Result& r)
    {
        _resultId = r.getResult();
        _time = max(_time, r.getTime());
        _memory = max(_memory, r.getMemory());
    }

    void print() { cout << _resultId << "\n" << _time << " " << _memory << "\n"; }

private:
    ResultId _resultId;
    int _time;
    int _memory;
};

#endif