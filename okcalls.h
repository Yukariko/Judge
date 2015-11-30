#ifndef _OKCALLS_H
#define _OKCALLS_H
#include <sys/syscall.h>
#define SYSCALL_MAX_LIMIT -1
#ifdef __i386
	#include "okcalls64.h"
#else
	#include "okcalls32.h"
#endif
#endif