#ifndef _JUDGEMENT_H
#define _JUDGEMENT_H

#include <iostream>
#include <algorithm>

#include "result.h"
#include "lang/language.h"
#include "data.h"

using namespace std;

class Judgement
{
public:
    Judgement(LangId langId, int probNo)
    {
        lang = Language::languageFactory(langId);
        data = Data::dataFactory(probNo);
    }

    Result doJudge()
    {
        Result result;
        if(!data.ready())
        {
            result.setResult(ResultId.OJMISS);
            return result;
        }
        if(compile(result))
            test(result);

        return result;
    }

private:
    bool compile(Result& result)
    {
        return lang->compile(result); 
    }

    void test(Result& result)
    {
        result = Result(ResultId.ACCEPT, 0, 0);

        for(DataIterator it = data->getIterator(); it.hasItem(); it.next())
        {
            Result curResult = lang->judge(it);
            result.setMax(curResult);

            if(!it.check(result))
                break;
        }
    }

    Language *lang;
    Data *data;
};

#endif