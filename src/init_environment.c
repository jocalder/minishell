#include "minishell.h"

static int	set_exp(t_mini *data, char *name, char *value)
{
	int	i;

	i = 0;
	while (data->cpy_envp[i])
		i++;
	data->cpy_envp = ft_realloc(data->cpy_envp, sizeof(char *) * (i + 2));
	data->cpy_envp[i] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (data->cpy_envp[i] == NULL)
		return (update_status(ERROR));
	ft_strlcpy(data->cpy_envp[i], name, ft_strlen(name));
	ft_strlcat(data->cpy_envp[i], "=", 1);
	ft_strlcat(data->cpy_envp[i], value, ft_strlen(value));
	data->cpy_envp[i + 1] = NULL;
	return (OK);
}

int	update_envp(t_mini *data)
{
	int		i;
	int		lvl;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (data->cpy_envp[++i])
	{
		if (ft_strncmp(data->cpy_envp[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(data->cpy_envp[i] + 6);
			free(data->cpy_envp[i]);
			tmp = ft_itoa(++lvl);
			if (!tmp)
				return (ERROR);
			data->cpy_envp[i] = ft_strjoin(ft_strdup("SHLVL="), tmp);
			if (!data->cpy_envp[i])
				return (free(tmp), ERROR);
			return (free(tmp), OK);
		}
	}
	if (!data->cpy_envp[i])
		if (set_exp(data, "SHLVL", "1") == ERROR)
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
