#include "minishell.h"

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
