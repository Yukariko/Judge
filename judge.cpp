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

void Judge::rtrim(char *str, int& len) const
{
	for(int i=len-1; i >= 0; i--)
	{
		if(str[i] != ' ' && str[i] != '\n')
			break;
		str[i] = 0;
		len--;
	}
}

int Judge::check(const string& answerPath, const string& outputPath)
{
	static char ansString[FSIZE_LIMIT + 100];
	static char outString[FSIZE_LIMIT + 100];

	FILE *ap = fopen(answerPath.c_str(), "r");
	if(ap == nullptr)
		return ACCEPT;

	FILE *op = fopen(outputPath.c_str(), "r");
	if(op == nullptr)
	{
		fclose(ap);
		return WRONG_ANSWER;
	}

	int ans = ACCEPT;

	while(fgets(ansString, sizeof(ansString), ap))
	{
		int alen = strlen(ansString);

		if(fgets(outString, sizeof(outString), op) == nullptr)
		{
			if(!feof(ap))
				ans = WRONG_ANSWER;
			if(alen == 1)
				break;
			outString[0] = 0;
		}

		int olen = strlen(outString);

		rtrim(ansString, alen);
		rtrim(outString, olen);

		if(alen != olen)
			ans = OUTPUT_FORMAT_WRONG;

		for(int ai=0, oi=0; ai < alen && oi < olen;)
		{
			int aSpaceLen = 0;
			int oSpaceLen = 0;
			while(ansString[ai] == ' ')
				ai++, aSpaceLen++;
			while(outString[oi] == ' ')
				oi++, oSpaceLen++;

			if(aSpaceLen != oSpaceLen)
			{
				ans = OUTPUT_FORMAT_WRONG;
				break;
			}

			while(ai < alen && oi < olen && ansString[ai] != ' ' && ansString[ai] == outString[oi])
				ai++, oi++;

			if(ansString[ai] != ' ' || ansString[ai] != 0 || outString[oi] != ' ' || outString[oi] != 0)
			{
				ans = WRONG_ANSWER;
				break;
			}
		}
		if(ans != ACCEPT)
			break;
	}

	fclose(ap);
	fclose(op);
	return ans;
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

		ans = check(answerPath, exec.getOutputPath());
		if(ans != ACCEPT)
		{
			resultAnswer = ans;
			return;
		}
		
		resultTime = max(resultTime, exec.getUsedTime());
		resultMemory = max(resultMemory, exec.getUsedMemory());

	}

	resultAnswer = ACCEPT;
	return;
}