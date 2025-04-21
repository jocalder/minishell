#include "minishell.h"

static void	init_data(t_mini *data)
{
	g_status = 0;
	data->input = NULL;
	data->prompt = NULL;
	data->args = NULL;
	data->prompt = NULL;
	data->info = ft_calloc(1, sizeof(t_prompt));
	if (!data->info)
		perror(FAIL_ALLOC);
	data->info->user = NULL;
	data->info->display = NULL;
	data->info->ptr = NULL;
	data->info->len = 0;
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
		data.input = readline(data.prompt);
		free(data.prompt);
		if (!data.input)
			return (1);
		if (*data.input)
			add_history(data.input);
		data.args = ft_split(data.input, ' ');
		execute_builtins(&data, envp);
		free(data.input);
	}
	rl_clear_history();
	exit (g_status);
}
