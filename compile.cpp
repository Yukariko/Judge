#include "compile.h"
#include "execute.h"

bool Compile::compile(Language& lang, const string& codePath)
{
	const char **compileCode = lang.getCompileCommand(codePath);
	int status = Execute::exec(compileCode);

	// Runtime Error
	if(status < 0)
	{
		return false;
	}
	return true;
}