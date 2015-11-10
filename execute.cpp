#include "execute.h"

int Execute::exec(const char **cmd)
{
	pid_t pid = fork();

	// child process
	if(pid == 0)
	{
		execlv(cmd[0], cmd);
		exit(0);
	}

	// parent process
	else
	{
		int status = 0;
		waitpid(pid, &status, 0);
		return status;
	}
}