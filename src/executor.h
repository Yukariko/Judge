#ifndef _EXECUTE_H
#define _EXECUTE_H


class Result
{
public:
    enum ResultId {
        EMPTY, NO_RESULT, READY, RUNNING, ACCEPT, WRONG_ANSWER, COMPILE_ERROR,
        RUNTIME_ERROR, TIME_LIMIT_EXCEED, MEMORY_LIMIT_EXCEED, OUTPUT_LIMIT_EXCEED,
        OUTPUT_FORMAT_WRONG, OJ_MISS
    };

    Result(ResultId resultId, int time = -1, int memory = -1) : _resultId(resultId),
        _time(time), _memory(memory) {}

    Result(const Result& result) : _resultId(result._resultId),
        _time(result._time), _memory(result._memory) {}

    ResultId getResult( return _resultId; )
    int getTime() { return _time; }
    int getMemory() { return _memory; }

    void print() { cout << _resultId << "\n" << _time << " " << _memory; }

private:
    ResultId _resultId;
    int _time;
    int _memory;
}

class Executor
{
public:
    static Result execute(const Language& language, const Data& data);
};

class CompileExecutor : public Executor
{
public:
    static Result execute(const Language& language, const Data& data);
};

class JudgeExecutor : public Executor
{
public:
    static Result execute(const Language& language, const Data& data);
};

#endif