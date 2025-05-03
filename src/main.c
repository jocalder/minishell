#include "minishell.h"

int	g_status;

static void	exit_status(int status, t_mini *data)
{
	if (status == END)
		g_status = 0;
	else if (status == ERROR)
		g_status = 1;
	else
		g_status = status;
	free_all(data, true);
	rl_clear_history();
	exit (g_status);
}

static void	check_state(int state, t_mini *data)
{
	if (state == OK)
		return ;
	else if (state == END)
	{
		printf("exit\n");
		exit_status(END, data);
	}
	else
		exit_status(state, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;
	int		state;

	(void)envp;
	if (argc > 1)
		return (perror(USAGE), E_USAGE);
	if (init_data(&data) == ERROR)
		return (perror("Error"), 1);
	wait_signal();
	while (argv)
	{
		if (set_prompt((&data)->prompt) == ERROR)
			exit_status(ERROR, &data);
		state = set_input(&data);
		check_state(state, &data);
		//execute_builtins(&data, envp); //before need execute others
		free_all(&data, false);
	}
	free_all(&data, true);
	rl_clear_history();
	exit (g_status);
}
