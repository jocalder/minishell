#include "minishell.h"

int	g_status;

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
