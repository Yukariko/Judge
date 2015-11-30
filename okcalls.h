#ifndef _OKCALLS_H
#define _OKCALLS_H
#include <sys/syscall.h>
#define SYSCALL_MAX_LIMIT -1
#if __x86_64__ || __ppc64__
	#include "okcalls64.h"
#else
	#include "okcalls32.h"
#endif
#endif