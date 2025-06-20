#include "minishell.h"

void	exit_free(void *buffer, int status, bool check, t_buffer_type type)
{
	if (!buffer)
		exit(status);
	if (type == IS_MINI)
		free_all(buffer, check);
	else if (type == IS_ENVP)
		free_envp(buffer, check);
	else if (type == IS_PROMPT)
		free_prompt(buffer, check);
	else if (type == IS_INPUT)
		free_input(buffer, check);
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
