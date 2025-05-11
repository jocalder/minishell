#include "minishell.h"

int	g_status;

static void	exit_status(int status, t_mini *data)
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

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)envp;
	if (argc != 1)
		return (perror(USAGE), E_USAGE);
	if (init_data(&data) == ERROR)
		return (free_all(&data, true), ERROR);
	wait_signal();
	while (argv)
	{
		if (set_prompt((&data)->prompt) != OK)
			exit_status(g_status, &data);
		if (set_input(&data) != OK)
			exit_status(g_status, &data);
		/*test*/
		printf_input(data.input);
		//execute_builtins(&data, envp); //before need execute others
		free_all(&data, false);
	}
	exit_status(g_status, &data);
}
