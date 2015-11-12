#include "judge.h"
#include <algorithm>

Judge::Judge(const string& lang, const string& dataPath)
{
	data.setDataPath(dataPath);
	exec.setLanguage(lang);
	exec.setOutputPath("test.out");
	exec.setErrorPath("test.err");
}

bool Judge::compile()
{
	int status = exec.exec(true);
	
	// Runtime Error
	if(status != 0)
		return false;
	return true;
}

int Judge::run()
{
	int status = exec.exec(false, data.getTimeLimit(), data.getMemoryLimit());
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
		cout << resultTime << " " << resultMemory / 1024 << endl;
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
		if(ans != ACCEPT)
		{
			resultAnswer = ans;
			return;
		}

		if(!check(answerPath, exec.getOutputPath()))
		{
			resultAnswer = WRONG_ANSWER;
			return;
		}
		
		resultTime = max(resultTime, exec.getUsedTime());
		resultMemory = max(resultMemory, exec.getUsedMemory());

	}

	resultAnswer = ACCEPT;
	return;
}