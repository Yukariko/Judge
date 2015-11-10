#ifndef _EXECUTE_H
#define _EXECUTE_H

#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

using namespace std;

class Execute
{
public:
	int exec(const char **cmd);
};

#endif