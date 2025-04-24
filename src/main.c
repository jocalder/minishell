#include "minishell.h"

static void	alloc_data(t_mini *data)
{
	data->args = NULL;
	data->prompt = NULL;
	data->input = NULL;
	data->prompt = ft_calloc(1, sizeof(t_prompt));
	data->input = ft_calloc(1, sizeof(t_input));
	if (!data->prompt || !data->input)
		perror(FAIL_ALLOC);
	data->prompt->prompt = NULL;
	data->prompt->cwd = NULL;
	data->prompt->user = NULL;
	data->prompt->display = NULL;
	data->prompt->len = 0;
	data->input->input = NULL;
	data->input->cmd = NULL;
	data->input->pipes = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)argv;
	if (argc > 1)
		perror(USAGE);
	alloc_data(&data);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		set_prompt((&data)->prompt);
		set_input(&data, (&data)->prompt->prompt);
		execute_builtins(&data, envp); //before need execute others
		free((&data)->input->input); //or free_all
	}
	rl_clear_history();
	exit (g_status);
}
