#include "minishell.h"

int	g_status;

static void	exit_status(int status, t_mini *data, int flag)
{
	if (status == ERROR)
		g_status = 1;
	if (flag == PROMPT)
		free_prompt(data->prompt, true);
	else if (flag == INPUT)
		free_input(data->input, true);
	rl_clear_history();
	exit (g_status);
}

static void	check_state(int state, t_mini *data)
{
	if (state == OK)
		return ;
	else if (state == ERROR)
		exit_status(state, data, INPUT);
	else if (state == END)
	{
		printf("exit\n");
		exit_status(0, data, INPUT);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;
	int		state;

	(void)argv;
	if (argc > 1)
		return (perror(USAGE), E_USAGE);
	if (init_data(&data) == ERROR)
		return (perror("Error"), 1);
	wait_signal();
	while (1)
	{
		if (set_prompt((&data)->prompt) == ERROR)
			exit_status(ERROR, &data, PROMPT);
		state = set_input(&data);
		check_state(state, &data);
		free_all(&data, false);
		execute_builtins(&data, envp); //before need execute others
	}
	free_all(&data, true);
	rl_clear_history();
	exit (g_status);
}
