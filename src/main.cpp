#include <cstdio>
#include <cstdlib>
#include "lang/language.h"
#include "result.h"
#include "judgement.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Usage: %s langId probId\n", argv[0]);
        return 0;
    }

    LangId langId = (LangId)atoi(argv[1]);
    int probId = atoi(argv[2]);
    Judgement judge(langId, probId);
    Result result = judge.doJudge();
    result.print();
    return 0;
}