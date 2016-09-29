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
        Result result(ACCEPT, 0, 0);
        if(!data->ready())
        {
            result.setResult(OJ_MISS);
            return result;
        }
        if(compile(result))
            test(result);

        return result;
    }

private:
    bool compile(Result& result)
    {
        return lang->compile("test"); 
    }

    void test(Result& result)
    {
        for(DataIterator it = data->getIterator(); it.hasItem(); it.next())
        {
            Result curResult = lang->judge("test", it);
            result.setMax(curResult);

            if(!it.check(result, "output.txt"))
                break;
        }
    }

    Language *lang;
    Data *data;
};

#endif