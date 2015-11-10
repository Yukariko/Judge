#ifndef _COMPILE_CPP
#define _COMPILE_CPP

#include <iostream>
#include "language.h"

using namespace std;

class Compile
{
public:
	static bool compile(Language& lang, const string& codePath);

};

#endif