#include "minishell.h"

void	free_envp(t_mini *data, bool check)
{
	if (!data || !check)
		return ;
	if (data->cpy_envp)
		free_array(data->cpy_envp, -1);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	data->cpy_envp = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
}
