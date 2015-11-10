#include "judge.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
	if(argc != 8)
	{
		cout << "Usage: " << argv[0] << " " << "lang codePath inputPath outputPath errorPath timeLimit memoryLimit" << endl;
		return 0;
	}

	Judge judge(argv[1], argv[2], argv[3], argv[4], argv[5], atoi(argv[6]), atoi(argv[7]));
	return 0;
}