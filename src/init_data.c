#include "minishell.h"

static void	sort_list(t_vars **head, t_vars *cur)
{
	//
}

static void	init_environment(t_mini *data, char **envp)
{
	if (!data->environment)
		return ;
	data->environment->value = NULL;
	data->environment->vars = NULL;
	if (!envp || !*envp || !**envp)
		handler_envp(&data->environment);
	else
	{
		data->environment->value = envpdup(envp);
		if (!data->environment->value)
			exit_free(data->environment, ERROR, IS_ENVP);
		udpate_envp(&data->environment);
		create_exp_vars();
	}
	sort_list(&(data->environment)->vars, data->environment->vars);
	data->environment->pwd = NULL;
	data->environment->oldpwd = NULL;
	data->environment->pwd = getcwd(NULL, 0);
	if (!data->environment->pwd)
		exit_free(data->environment, ERROR, IS_ENVP);
	data->environment->oldpwd = getcwd(NULL, 0);
	if (!data->environment->oldpwd)
		exit_free(data->environment, ERROR, IS_ENVP);
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
	init_environment(data, envp);
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
		exit_free(data->prompt, ERROR, IS_PROMPT);
	}
	init_prompt(data->prompt);
	init_input(data->input);
}
