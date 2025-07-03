#include "minishell.h"

/*In case that bash add '=' if export VAR (without '=')*/
// int	set_new_var(t_mini *data, char *new_var, int i, bool export)
// {
// 	char	***ptr;
// 	char	**tmp;

// 	ptr = NULL;
// 	if (export)
// 		ptr = &data->exp_vars;
// 	else
// 		ptr = &data->vars;
// 	tmp = ft_realloc(ptr[0], sizeof(char *) * (i + 2));
// 	if (!tmp)
// 		return (update_status(ERROR));
// 	ptr[0] = tmp;
// 	if (ft_strchr(new_var, '='))
// 		ptr[0][i] = ft_calloc(ft_strlen(new_var) + 1,
// 				sizeof(char));
// 	else
// 		ptr[0][i] = ft_calloc((ft_strlen(new_var) + 2),
// 				sizeof(char));
// 	if (!ptr[0][i])
// 		return (update_status(ERROR));
// 	ft_strcpy(ptr[0][i], new_var);
// 	if (!ft_strchr(new_var, '='))
// 		ft_strlcat(ptr[0][i], "=", (ft_strlen(new_var) + 2));
// 	ptr[0][i + 1] = NULL;
// 	return (OK);
// }

int	set_new_var(t_mini *data, char *new_var, int i, bool export)
{
	char	***ptr;
	char	**tmp;

	ptr = NULL;
	if (export)
		ptr = &data->exp_vars;
	else
		ptr = &data->vars;
	tmp = ft_realloc(ptr[0], sizeof(char *) * (i + 2));
	if (!tmp)
		return (update_status(ERROR));
	ptr[0] = tmp;
	prt[0][i] = ft_strdup(new_var);
	if (!ptr[0][i])
		return (update_status(ERROR));
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

// int	unset_var(t_mini *data, char *var, bool export)
// {
// 	int		i;
// 	char	***ptr;

// 	i = 0;
// 	ptr = NULL;
// 	if (export)
// 		ptr = &data->exp_vars;
// 	else
// 		ptr = &data->vars;
// 	while (ptr[0][i])
// 	{
// 		if (is_same_var(ptr[0][i], var))
// 		{
// 			//
// 		}
// 		i++;
// 	}
// }

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
		if (set_new_var(data, "SHLVL=1", i, true) == ERROR)
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
