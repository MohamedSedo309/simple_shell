#include "shell.h"

void initialize_shell(char **curcmd, int cmdtyp)
{
	pid_t mypid;

	if (cmdtyp == EXTERNAL_COMMAND || cmdtyp == PATH_COMMAND)
	{
		mypid = fork();
		if (mypid == 0)
			execute_input_command(curcmd, cmdtyp);
		else
		{
			waitpid(mypid, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_input_command(curcmd, cmdtyp);
}