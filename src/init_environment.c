#include "minishell.h"

int	mini_envp(t_mini *data)
{
	char	*tmp;
	char	*pwd;

	if (set_new_var(&data->envp, "OLDPWD", count_str(data->envp)) != 0)
		return (update_status(ERROR));
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (update_status(ERROR));
	pwd = ft_strjoin(ft_strdup("PWD="), tmp);
	if (set_new_var(&data->envp, pwd, count_str(data->envp)) != OK)
		return (update_status(ERROR));
	free(pwd);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(ft_strdup("_="), "/usr/bin/env");
	if (set_new_var(&data->envp, tmp, count_str(data->envp)) != OK)
		return (update_status(ERROR));
	free(tmp);
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

int	update_envp(t_mini *data)
{
	int		i;
	int		lvl;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(data->envp[i] + 6);
			free(data->envp[i]);
			tmp = ft_itoa(++lvl);
			if (!tmp)
				return (ERROR);
			data->envp[i] = ft_strjoin(ft_strdup("SHLVL="), tmp);
			if (!data->envp[i])
				return (free(tmp), ERROR);
			return (free(tmp), OK);
		}
	}
	if (!data->envp[i])
		if (set_new_var(&data->envp, "SHLVL=1", i) == ERROR)
			return (ERROR);
	return (OK);
}
