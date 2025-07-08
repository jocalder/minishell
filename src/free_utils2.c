#include "minishell.h"

void	free_envp(t_mini *data, bool check)
{
	if (!data || !check)
		return ;
	if (data->envp)
		free_array(data->envp, -1);
	if (data->exp_vs)
		free_array(data->exp_vs, -1);
	if (data->vars)
		free_array(data->vars, -1);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	data->envp = NULL;
	data->exp_vs = NULL;
	data->vars = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
}
