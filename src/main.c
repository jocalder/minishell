#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	init_data(&data);
	wait_signal(0);
	if (isatty(STDIN_FILENO) && argc == 1)
		interactive_mode(&data, envp);
	else
		command_mode(&data, argv, argc, envp);
	exit (g_status);
}
