#include "judge.h"
#include "compile.h"

Judge::Judge(Language lang, const string& codePath, const string& inPath, const string& outPath)
	: lang(lang), codePath(codePath), inPath(inPath), outPath(outPath) 
{
	Compile compileManager(lang, codePath);

	string ans;

	// compile success
	if(compileManager.compile(ans))
	{

	}
	else
	{

	}

}