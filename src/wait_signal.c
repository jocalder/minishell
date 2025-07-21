/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:16:05 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/21 12:27:49 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = CTRC;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
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
		write(STDOUT_FILENO, "\n", 1);
		if (kill(getpid(), SIGKILL) == -1)
			write(STDERR_FILENO, "Error: kill\n", 13);
	}
	return ;
}

static void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	wait_signal(int i)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	disable_echoctl();
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
