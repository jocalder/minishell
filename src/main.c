#include "minishell.h"

static void	init_data(t_mini *data)
{
	g_status = 0;
	data->args = NULL;
	data->prompt = NULL;
	data->prompt = ft_calloc(1, sizeof(t_prompt));
	if (!data->prompt)
		perror(FAIL_ALLOC);
	data->prompt->prompt = NULL;
	data->prompt->user = NULL;
	data->prompt->display = NULL;
	data->prompt->ptr = NULL;
	data->prompt->len = 0;
	data->input = NULL;
	data->input = ft_calloc(1, sizeof(t_input));
	if (!data->input)
		perror(FAIL_ALLOC);
	data->input->cmd = NULL;
	data->input->pipes = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)argv;
	if (argc > 1)
		perror(USAGE);
	init_data(&data);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		set_prompt(&data);
		data.input->input = readline(data.prompt->prompt);
		free(data.prompt->prompt);
		if (!data.input->input)
			return (1);
		if (data.input->input)
			add_history(data.input->input);
		data.args = ft_split(data.input->input, ' ');
		execute_builtins(&data, envp);
		free(data.input->input);
	}
	rl_clear_history();
	exit (g_status);
}
