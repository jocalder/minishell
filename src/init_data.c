#include "minishell.h"

static void	init_environment(t_mini *data, char **envp)
{
	data->exp_vars = NULL;
	data->vars = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
	data->exp_vars = envpdup(envp);
	if (!data->exp_vars)
		exit(ERROR);
	if (update_envp(data) != OK)
	{
		free_array(data->exp_vars, -1);
		exit(ERROR);
	}
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		free_array(data->exp_vars, -1);
		exit(ERROR);
	}
	data->oldpwd = getcwd(NULL, 0);
	if (!data->oldpwd)
	{
		free_array(data->exp_vars, -1);
		free(data->pwd);
		exit (ERROR);
	}
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

static void	init_input(t_input *input)
{
	if (!input)
		return ;
	input->value = NULL;
	input->cmd = NULL;
	input->pipes = 0;
}

void	init_data(t_mini *data, char **envp)
{
	g_status = 0;
	data->prev_fd = -1;
	data->pid = getpid();
	data->prompt = NULL;
	data->input = NULL;
	init_environment(data, envp);
	data->prompt = ft_calloc(1, sizeof(t_prompt));
	if (!data->prompt)
	{
		free_envp(data, true);
		exit (ERROR);
	}
	data->input = ft_calloc(1, sizeof(t_input));
	if (!data->input)
	{
		free_envp(data, true);
		free_prompt(data->prompt, true);
		exit (ERROR);
	}
	init_prompt(data->prompt);
	init_input(data->input);
}
