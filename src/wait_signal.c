#include "minishell.h"

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = CTRC;
		rl_replace_line("", 0);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = CTRC;
		write(STDOUT_FILENO, "\n", 1);
	}
	return ;
}

static void	here_doc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = CTRC;
		write(1, "\n", 1);
		if (kill(getpid(), SIGKILL) == -1)
			write(STDERR_FILENO, "Error: kill\n", 13);
	}
	return ;
}

void	wait_signal(int i)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	signal(SIGQUIT, SIG_IGN);
	if (i == 0)
		sa.sa_handler = &sigint_handler;
	else if (i == 1)
		sa.sa_handler = &child_handler;
	else if (i == 2)
		sa.sa_handler = &here_doc_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
