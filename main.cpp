#include "judge.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Usage: " << argv[0] << " " << "lang dataPath" << endl;
		return 0;
	}

	Judge judge(langs[atoi(argv[1])], argv[2]);
	judge.doJudge();
	judge.printResult();
	return 0;
}