#include "judge.h"

Judge::Judge(const string& lang, const string& codePath, const string& dataPath)
	: lang(Language(lang)), codePath(codePath)
{
	data.setDataPath(dataPath);
	exec.setOutputPath("test.out");
	exec.setErrorPath("test.err");
}

bool Judge::compile()
{
	char * const *compileCommand = lang.getCompileCommand(codePath);
	int status = exec.exec(compileCommand);
	
	cout << status << endl;

	// Runtime Error
	if(status < 0)
		return false;
	return true;
}

int Judge::run()
{
	char * const *runCommand = lang.getRunCommand();
	int status = exec.exec(runCommand, data.getTimeLimit(), data.getMemoryLimit());
	return status;
}

bool Judge::check(const string& answerPath, const string& outputPath)
{

	return true;
}

void Judge::printResult()
{
	cout << resultAnswer << endl;
	if(resultAnswer == COMPILE_ERROR)
		cout << resultMessage << endl;
	else
		cout << resultTime << " " << resultMemory << endl;
}

void Judge::doJudge()
{
	if(!compile())
	{
		resultAnswer = COMPILE_ERROR;
		return;
	}

	resultTime = 0;
	resultMemory = 0;
	resultMessage = "";

	int tc = data.getTestCaseNum();

	for(int i=0; i < tc; i++)
	{
		const string& input = data.getInputPath(i);
		const string& answerPath = data.getOutputPath(i);

		exec.setInputPath(input);
		int ans = run();

		// error
		if(ans != 0)
		{
			resultAnswer = ans;
			return;
		}

		if(!check(answerPath, exec.getOutputPath()))
		{
			resultAnswer = WRONG_ANSWER;
			return;
		}
		
	}

	resultAnswer = ACCEPT;
	return;
}