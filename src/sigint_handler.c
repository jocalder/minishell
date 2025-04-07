#include "minishell.h"

int	g_status;

/*	
	This function handles the CTRL+C signal (SIGINT).
	It sets g_status to 130, which is the standard exit code for an interrupted command.
	It then prints a newline, clears the current input line, and resets the prompt using readline functions.
*/

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = CTRC;
		if (write(STDIN_FILENO, "\n", 1) == -1)
			perror(FAIL_WRITE);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}
