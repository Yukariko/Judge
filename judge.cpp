#include "judge.h"

Judge::Judge(const string& lang, const string& codePath, const string& inPath, const string& outPath, const string& errPath, int timeLimit, int memoryLimit)
	: lang(Language(lang)), codePath(codePath), outPath(outPath), timeLimit(timeLimit), memoryLimit(memoryLimit)
{
	exec.setInPath(inPath);
	exec.setOutPath("test.out");
	exec.setErrPath(errPath);
}

bool Judge::compile()
{
	const char **compileCommand = lang.getCompileCommand(codePath);
	int status = exec.exec(compileCommand);

	// Runtime Error
	if(status < 0)
		return false;
	return true;
}

int Judge::run()
{
	const char **runCommand = lang.getRunCommand();
	int status = exec.exec(runCommand, timeLimit, memoryLimit);


}