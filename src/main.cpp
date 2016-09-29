#include <cstdio>
#include <cstdlib>
#include "lang/language.h"
#include "result.h"
#include "judgement.h"
#include "log.h"

int main(int argc, char **argv)
{
    Log::terminate(argc != 3 || !isdigit(*argv[1]) || !isdigit(*argv[2]), "main");
    LangId langId = (LangId)atoi(argv[1]);
    int probId = atoi(argv[2]);
    Judgement judge(langId, probId);
    Result result = judge.doJudge();
    result.print();
    return 0;
}