#include "minishell.h"

int	set_new_var(t_mini *data, char *new_var, bool export)
{
	int		i;
	char	***ptr;

	i = 0;
	ptr = NULL;
	if (export)
		ptr = &data->exp_vars;
	else
		ptr = &data->vars;
	while (ptr[0][i])
		i++;
	ptr[0] = ft_realloc(ptr[0], sizeof(char *) * (i + 2));
	if (!ptr[0])
		return (update_status(ERROR));
	ptr[0][i] = ft_strdup(new_var);
	if (ptr[0][i] == NULL)
		return (free_array(ptr[0], -1), update_status(ERROR));
	ptr[0][i + 1] = NULL;
	return (OK);
}

int	set_existing_var(t_mini *data, char *var, bool export)
{
	int		i;
	char	***ptr;

	if (!ft_strchr(var, '='))
		return (OK);
	i = 0;
	ptr = NULL;
	if (export)
		ptr = &data->exp_vars;
	else
		ptr = &data->vars;
	while (ptr[0][i])
	{
		if (is_same_var(ptr[0][i], var))
		{
			free(ptr[0][i]);
			ptr[0][i] = NULL;
			ptr[0][i] = ft_strdup(var);
			if (!ptr[0][i])
				return (update_status(ERROR));
			return (OK);
		}
		i++;
	}
	return (OK);
}

int	unset_var(t_mini *data, char *var, bool export)
{
	int		i;
	char	***ptr;

	i = 0;
	ptr = NULL;
	if (export)
		ptr = &data->exp_vars;
	else
		ptr = &data->vars;
	while (ptr[0][i])
	{
		if (is_same_var(ptr[0][i], var))
		{
			//
		}
		i++;
	}
}

int	update_envp(t_mini *data)
{
	int		i;
	int		lvl;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (data->exp_vars[++i])
	{
		if (ft_strncmp(data->exp_vars[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(data->exp_vars[i] + 6);
			free(data->exp_vars[i]);
			tmp = ft_itoa(++lvl);
			if (!tmp)
				return (ERROR);
			data->exp_vars[i] = ft_strjoin(ft_strdup("SHLVL="), tmp);
			if (!data->exp_vars[i])
				return (free(tmp), ERROR);
			return (free(tmp), OK);
		}
	}
	if (!data->exp_vars[i])
		if (set_new_var(data, "SHLVL=1", true) == ERROR)
			return (ERROR);
	return (OK);
}

char	**envpdup(char **envp)
{
	char	**cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			while (i >= 0)
				free(cpy[i--]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
