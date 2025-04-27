#include "minishell.h"

int	g_status;

int	exit_status(int status, t_mini *data, int flag)
{
	if (status == ERROR)
		g_status = 1;
	if (flag == PROMPT)
		free_prompt(data->prompt);
	else if (flag == INPUT)
		free_input(data->input);
	rl_clear_history();
	exit (g_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)envp;
	if (argc > 1)
		return (perror(USAGE), E_USAGE);
	if (init_data(&data) == ERROR)
		return (perror("Error"), 1);
	wait_signal();
	while (argv)
	{
		if (set_prompt((&data)->prompt) == ERROR)
			exit_status(ERROR, &data, PROMPT);
		if (set_input(&data) == (ERROR))
			exit_status(ERROR, &data, INPUT);
		free_input((&data)->input);
		//execute_builtins(&data, envp); //before need execute others
	}
	free_all(&data);
	rl_clear_history();
	exit (g_status);
}
