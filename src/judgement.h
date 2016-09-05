#ifndef _JUDGEMENT_H
#define _JUDGEMENT_H

#include <iostream>
#include <algorithm>

#include "language.h"
#include "executor.h"
#include "data.h"

using namespace std;

class Judgement
{
public:
    Judgement(LangId langId, int probNo)
    {
        Language *language = Language.languageFactory(langId);
        Data data(probNo);

        _result = CompileExecutor.execute(*language, data);
        if(_result.getResult() != Result.ResultId.ACCEPT)
            return;

        int tc = data.getTestCaseCount();

        _result = Result(Result.ResultId.ACCEPT, 0, 0);

        for(int i=0; i < tc; i++)
        {

            Result result = JudgeExecutor(*language, data);
            if(result.getResult() != Executor.ResultId.ACCEPT)
            {
                _result = Result(result.getResult());
                return;
            }

            _result = Result(Result.ResultId.ACCEPT,
                             max(_result.getTime(), result.getTime()),
                             max(_result.getMemory(), result.getMemory()));


            result = check(data);
            if(result.getResult() != Executor.ResultId.ACCEPT)
            {
                _result = Result(result.getResult());
                return;
            }
        }

        _result.print();
    }

private:
    Result check(const Data& data);

    Result _result;
};

#endif