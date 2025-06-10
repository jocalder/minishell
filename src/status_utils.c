#include "minishell.h"

void	exit_free(t_mini *data, int status, bool check)
{
	free_all(data, check);
	exit(status);
}

int	update_status(int new_status)
{
	g_status = new_status;
	return (g_status);
}

void	check_exit_status(int status, t_mini *data)
{
	if (status == END || status == ERROR)
	{
		if (status == END)
		{
			printf("exit\n");
			g_status = 0;
		}
		free_all(data, true);
		rl_clear_history();
		exit (g_status);
	}
}
