#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	if (argc != 1)
		return ((void)write(STDERR_FILENO, USAGE, 20), update_status(SINTAX));
	if (init_data(&data) != OK)
		return (free_all(&data, true), update_status(ERROR));
	wait_signal();
	while (argv)
	{
		if (set_prompt((&data)->prompt) != OK)
			check_exit_status(g_status, &data);
		if (set_input(&data) != OK)
			check_exit_status(g_status, &data);
		handle_execution(&data, envp); // Needs a errors protection
		free_all(&data, false);
	}
	exit_status(g_status, &data);
}
