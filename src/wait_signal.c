#include "minishell.h"

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = CTRC;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	wait_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
