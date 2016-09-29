#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include "result.h"

class Log
{
public:
    static void terminate(const string& msg = "")
    {
        Result result(OJ_MISS);
        result.print();
        if(msg.length() > 0)
            cout << msg << '\n';
        exit(0);
    }
    static void terminate(bool tf, const string& msg = "")
    {
        if(!tf)
            return;
        terminate(msg);
    }
};

#endif 