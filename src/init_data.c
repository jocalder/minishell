#include "minishell.h"

void	free_all(t_mini *data, bool check)
{
	if (!data)
		return ;
	free_envp(data->environment, check);
	free_prompt(data->prompt, check);
	free_input(data->input, check);
}

static void	init_environment(t_envp *environment, char **envp)
{
	if (!environment)
		return ;
	environment->value = NULL;
	if (!envp || !*envp || !**envp)
		handler_envp(environment);
	else
	{
		environment->value = envpdup(envp);
		if (!environment->value)
			exit_free(environment, ERROR, true, IS_ENVP);
	}
	environment->pwd = NULL;
	environment->oldpwd = NULL;
	environment->pwd = getcwd(NULL, 0);
	if (!environment->pwd)
		exit_free(environment, ERROR, true, IS_ENVP);
	environment->oldpwd = getcwd(NULL, 0);
	if (!environment->oldpwd)
	{
		free(environment->pwd);
		exit_free(environment, ERROR, true, IS_ENVP);
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
	data->environment = NULL;
	data->prompt = NULL;
	data->input = NULL;
	data->environment = ft_calloc(1, sizeof(t_envp));
	if (!data->environment)
		exit(ERROR);
	init_environment(data->environment, envp);
	data->prompt = ft_calloc(1, sizeof(t_prompt));
	if (!data->prompt)
	{
		free_envp(data->environment, true);
		exit(ERROR);
	}
	data->input = ft_calloc(1, sizeof(t_input));
	if (!data->input)
	{
		free_envp(data->environment, true);
		free_prompt(data->prompt, true);
		exit(ERROR);
	}
	init_prompt(data->prompt);
	init_input(data->input);
}
