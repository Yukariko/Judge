#include <cstdio>
#include <cstdlib>
#include "lang/language.h"
#include "result.h"
#include "judgement.h"
#include "log.h"

int main(int argc, char **argv)
{
    if(argc != 3 || !isdigit(*argv[1]) || !isdigit(*argv[2]))
    {
        Log::terminate("Usage: %s langId probId\n", argv[0]);
        return 0;
    }

    LangId langId = (LangId)atoi(argv[1]);
    int probId = atoi(argv[2]);
    Judgement judge(langId, probId);
    Result result = judge.doJudge();
    result.print();
    return 0;
}