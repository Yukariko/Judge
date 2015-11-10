#include "judge.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout << "Usage: " << argv[0] << " " << "lang codePath dataPath" << endl;
		return 0;
	}

	Judge judge(argv[1], argv[2], argv[3]);
	return 0;
}