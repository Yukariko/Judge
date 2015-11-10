#include "judge.h"

Judge::Judge(const string& lang, const string& codePath, const string& dataPath)
	: lang(Language(lang)), codePath(codePath)
{
	data.setDataPath(dataPath);
	exec.setOutPath("test.out");
	exec.setErrPath("test.err");
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
	int status = exec.exec(runCommand, data.getTimeLimit(), data.getMemoryLimit());
	return status;
}

int Judge::doJudge()
{
	if(!compile())
		return COMPILE_ERROR;

	int tc = data.getTestCaseNum();

	for(int i=0; i < tc; i++)
	{
		const string& input = data.getInputPath(i);
		const string& output = data.getoutputPath(i);

		exec.setInputPath(input);
		int ans = run();

		// error
		if(ans != 0)
			return ans;

		if(!check())
			return WRONG_ANSWER;
		
	}

	return ACCEPT;
}