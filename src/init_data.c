#include "minishell.h"

static void	init_input(t_input *input)
{
	if (!input)
		return ;
	input->value = NULL;
	input->cmd = NULL;
	input->pipes = 0;
}

static void	init_prompt(t_prompt *prompt)
{
	if (!prompt)
		return ;
	prompt->value = NULL;
	prompt->cwd = NULL;
	prompt->user = NULL;
	prompt->display = NULL;
	prompt->len = 0;
}

int	init_data(t_mini *data)
{
	g_status = 0;
	data->prompt = NULL;
	data->input = NULL;
	data->prompt = ft_calloc(1, sizeof(t_prompt));
	if (!data->prompt)
		return (ERROR);
	data->input = ft_calloc(1, sizeof(t_input));
	if (!data->input)
		return (free(data->prompt), ERROR);
	init_prompt(data->prompt);
	init_input(data->input);
	return (OK);
}
