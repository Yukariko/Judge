#include "judge.h"
#include <algorithm>
#include <cstring>

Judge::Judge(const string& lang, const string& dataPath)
{
	data.setDataPath(dataPath);
	exec.setLanguage(lang, "test");
	exec.setOutputPath("test.out");
	exec.setErrorPath("test.err");
	if(data.isSpecialJudge())
	{
		spjExec.setLanguage(data.getSpecialJudgeLang(), "spj");
		spjExec.setInputPath("test.out");
		spjExec.setOutputPath("spj.out");
		spjExec.setErrorPath("spj.err");
	}
}

void Judge::rtrim(char *str, int& len)
{
	for(int i=len-1; i >= 0; i--)
	{
		if(str[i] != ' ' && str[i] != '\n')
			break;
		str[i] = 0;
		len--;
	}
}

int Judge::check(const string& spjPath)
{
	FILE *sp = fopen(spjPath.c_str(), "r");
	if(sp == nullptr)
		return WRONG_ANSWER;

	int ans = fgetc(sp);
	fclose(sp);
	return ans == '1'? ACCEPT: WRONG_ANSWER;
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
			if(fgetc(ap) != EOF)
			{
				ans = WRONG_ANSWER;
				break;
			}
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

			if((ansString[ai] != ' ' && ansString[ai] != 0) || (outString[oi] != ' ' && outString[oi] != 0))
			{
				ans = WRONG_ANSWER;
				break;
			}
		}
		if(ans != ACCEPT)
			break;
	}

	if(ans == ACCEPT)
	{
		int next = fgetc(op);
		if(next != EOF && next != '\n')
			ans = OUTPUT_LIMIT_EXCEED;
		else if(next == '\n')
		{
			next = fgetc(op);
			if(next != EOF)
				ans = OUTPUT_LIMIT_EXCEED;
		}
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
	if(!exec.compile())
	{
		resultAnswer = COMPILE_ERROR;
		return;
	}

	if(data.isSpecialJudge() && !spjExec.compile())
	{
		resultAnswer = OJ_MISS;
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
		int ans = exec.run(data.getTimeLimit(), data.getMemoryLimit());

		// error
		if(ans != ACCEPT)
		{
			resultAnswer = ans;
			return;
		}

		if(data.isSpecialJudge())
		{
			ans = spjExec.run(60, 128);
			if(ans != ACCEPT)
			{
				resultAnswer = WRONG_ANSWER;
				return;
			}
			else
				ans = check(spjExec.getOutputPath());
		}
		else
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