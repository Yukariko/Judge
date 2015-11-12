#include "language.h"
#include <cstring>
#include <unistd.h>

Language::Language() : langIdx(-1), compileCommand(nullptr), runCommand(nullptr) {}

Language::Language(const string& lang)
{
	langIdx = 0;
	while(langs[langIdx] != nullptr && lang != langs[langIdx])
		langIdx++;

	if(langs[langIdx] == nullptr)
	{
		cerr << "Invalid Language" << endl;
		exit(1);
	}

	compileCommand = nullptr;
	runCommand = nullptr;

	initCommand();
}

Language::Language(const Language& lang) : langIdx(lang.langIdx)
{
	initCommand();
}

Language::~Language() 
{
	if(compileCommand)
		delete[] compileCommand;

	if(runCommand)
		delete[] runCommand;
}

Language& Language::operator= (const Language& lang)
{
	langIdx = lang.langIdx;
	initCommand();
	return *this;
}

void Language::initCommand()
{
	if(compileCommand)
		delete[] compileCommand;

	if(runCommand)
		delete[] runCommand;

	switch(langIdx)
	{
	case C:
		compileCommand = new const char *[11] {"gcc", "test.c", "-o", "test", "-std=c99", "-O2", "--static", "-Wall", "-lm", "-DONLINE_JUDGE", nullptr};
		runCommand = new const char *[2] {"./test", nullptr};
		break;
	case CPP:
		compileCommand = new const char *[10] {"g++", "test.cpp", "-o", "test", "-O2", "--static", "-Wall", "-lm", "-DONLINE_JUDGE", nullptr};
		runCommand = new const char *[2] {"./test", nullptr};
		break;
	case CPP11:
		compileCommand = new const char *[11] {"g++", "test.cpp", "-o", "test", "-std=c++11", "-O2", "--static", "-Wall", "-lm", "-DONLINE_JUDGE", nullptr};
		runCommand = new const char *[2] {"./test", nullptr};
		break;
	case JAVA:
		break;
	}
}

char * const *Language::getCompileCommand() const
{
	return (char * const *)compileCommand;
}

char * const *Language::getRunCommand() const
{
	return (char * const *)runCommand;
}

int Language::getCpuUsage(struct rusage& ruse) const
{
	int usedTime;
	usedTime = (ruse.ru_utime.tv_sec * 1000) + (ruse.ru_utime.tv_usec / 1000);
	usedTime += (ruse.ru_stime.tv_sec * 1000) + (ruse.ru_stime.tv_usec / 1000);
	return usedTime;
}

int Language::getMemoryUsage(int pid, struct rusage& ruse) const
{
	if(langIdx == JAVA)
		return ruse.ru_minflt * getpagesize();

	char fn[4096], buf[4096];
	sprintf(fn, "/proc/%d/status", pid);

	FILE *pf = fopen(fn, "r");
	int m = strlen("VmPeak: ");

	int ret = 0;
	while(pf && fgets(buf, 4096 - 1, pf))
	{
		buf[strlen(buf) - 1] = 0;
		if(strncmp(buf, "VmPeak: ", m) == 0)
			sscanf(buf + m + 1, "%d", &ret);
	}
	if(pf)
		fclose(pf);
	return ret * 1024 * 1024;
}

bool Language::isSafeExit(int exitcode) const
{
	if(exitcode == 0x05 || exitcode == 0)
		return true;
	return false;
}

void Language::initCallCounter(int *callCounter) const
{
	memset(callCounter, 0, 512 * sizeof(int));
	if(langIdx == C || langIdx == CPP || langIdx == CPP11) // C & C++
		for(int i=0; i==0||LANG_CV[i]; i++)
			callCounter[LANG_CV[i]] = SYSCALL_MAX_LIMIT;
	else if(langIdx == JAVA)
		for(int i=0; i==0||LANG_JV[i]; i++)
			callCounter[LANG_JV[i]] = SYSCALL_MAX_LIMIT;
}
/*
} else if (lang == 2) { // Pascal
				for (i = 0; i==0||LANG_PV[i]; i++)
								call_counter[LANG_PV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 4) { // Ruby
				for (i = 0; i==0||LANG_RV[i]; i++)
								call_counter[LANG_RV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 5) { // Bash
				for (i = 0; i==0||LANG_BV[i]; i++)
								call_counter[LANG_BV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 6) { // Python
				for (i = 0; i==0||LANG_YV[i]; i++)
								call_counter[LANG_YV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 7) { // php
				for (i = 0; i==0||LANG_PHV[i]; i++)
								call_counter[LANG_PHV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 8) { // perl
				for (i = 0; i==0||LANG_PLV[i]; i++)
								call_counter[LANG_PLV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 9) { // mono c#
				for (i = 0; i==0||LANG_CSV[i]; i++)
								call_counter[LANG_CSV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 10) { //objective c
				for (i = 0; i==0||LANG_OV[i]; i++)
								call_counter[LANG_OV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 11) { //free basic
				for (i = 0; i==0||LANG_BASICV[i]; i++)
								call_counter[LANG_BASICV[i]] = HOJ_MAX_LIMIT;
} else if (lang == 12) { //scheme guile
				for (i = 0; i==0||LANG_SV[i]; i++)
								call_counter[LANG_SV[i]] = HOJ_MAX_LIMIT;
}
*/