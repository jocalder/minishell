#include "minishell.h"

void	exit_free(t_mini *data, int status)
{
	if (status == ERROR || status == ERROR_FD)
		status = 1;
	free_all(data, true);
	rl_clear_history();
	exit(status);
}

int	update_status(int new_status)
{
	g_status = new_status;
	return (g_status);
}

void	check_exit_status(int status, t_mini *data)
{
	if (status == ERROR_FD)
		g_status = 1;
	else if (status == ERROR)
	{
		g_status = 1;
		free_all(data, true);
		rl_clear_history();
		exit (g_status);
	}
}
