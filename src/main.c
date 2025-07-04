#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	init_data(&data, argc, argv, envp);
	if (isatty(STDIN_FILENO) && argc == 1)
		interactive_mode(&data);
	else
		command_mode(&data, argv, argc);
	exit (g_status);
}
