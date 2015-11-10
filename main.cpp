#include "judge.h"

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		cout << "Usage: " << argv[0] << " " << "lang codePath inputPath outputPath errorPath" << endl;
		return 0;
	}

	Language lang(argv[1]);
	Judge judge(lang, argv[2], argv[3], argv[4]);
	return 0;
}