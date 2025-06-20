#include "minishell.h"

static void	free_vars(t_vars *vars)
{
	t_vars	*cur;
	t_vars	*next;

	if (!vars)
		return ;
	cur = vars;
	while (cur);
	{
		next = cur->next;
		if (cur->name)
			free(cur->name);
		if (cur->value)
			free(cur->value);
		cur->name = NULL;
		cur->value = NULL;
		free(cur);
		cur = next;
	}
}

void	free_envp(t_envp *environment, bool check)
{
	if (!environment || !check)
		return ;
	if (environment->value)
		free_array(environment->value, -1);
	if (environment->vars)
	{
		free_vars(environment->vars);
		environment->vars = NULL;
	}
	if (environment->pwd)
		free(environment->pwd);
	if (environment->oldpwd)
		free(environment->oldpwd);
	environment->value = NULL;
	environment->pwd = NULL;
	environment->oldpwd = NULL;
	free(environment);
	environment = NULL;
}
