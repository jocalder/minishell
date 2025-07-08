#include "minishell.h"

static void	init_export_vars(t_mini *data, char **envp)
{
	if (!data)
		exit (ERROR);
	if (!envp || !*envp || !**envp)
	{
		if (mini_envp(data) == ERROR)
			exit_free(data, ERROR);
		data->exp_vs = envpdup(data->envp);
		if (!is_existing_var(data->envp, "PATH=/usr/local/bin:/usr/bin:/bin"))
			if (set_new_var(&data->envp, "PATH=/usr/local/bin:/usr/bin:/bin",
					count_str(data->envp)) == ERROR)
				exit_free(data, ERROR);
	}
	else
	{
		data->envp = envpdup(envp);
		if (!data->envp)
			exit (ERROR);
		data->exp_vs = envpdup(data->envp);
	}
	if (update_envp(data) != OK)
		exit_free(data, ERROR);
	if (!data->exp_vs)
		exit_free(data, ERROR);
}

static void	init_environment(t_mini *data, char **envp)
{
	data->envp = NULL;
	data->exp_vs = NULL;
	data->vars = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
	init_export_vars(data, envp);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		exit_free(data, ERROR);
	data->oldpwd = ft_strdup("");
	if (!data->oldpwd)
		exit_free(data, ERROR);
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
		free_prompt(&data->prompt, true);
		exit (ERROR);
	}
	init_prompt(data->prompt);
	init_input(data->input);
}
