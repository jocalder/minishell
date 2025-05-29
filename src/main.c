#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

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
		//invented_input(data.input);
		printf_input(data.input);
		handle_execution(&data, envp);
		/*end_test*/
		free_all(&data, false);
	}
	exit_status(g_status, &data);
}
