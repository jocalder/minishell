#include "minishell.h"

void	handler_envp(t_envp **environment)
{
	if (create_envp(*environment) == ERROR)
		exit_free(*environment, ERROR, IS_ENVP);
	if (create_exp_vars(*environment) == ERROR)
		exit_free(*environment, ERROR, IS_ENVP);
	if (create_path_no_env(*environment) == ERROR)
		exit_free(*environment, ERROR, IS_ENVP);
}

char	**envpdup(char **envp)
{
	char	cpy;
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

static void	set_exp(t_envp **env, char *name, char *value)
{
	int	i;

	i = 0;
	while ((*env)->value[i])
		i++;
	(*env)->value = ft_realloc((*env), sizeof(char *), (i + 2));
	(*env)->value[i] = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!(*env)->value[i])
		exit_free((*env), ERROR, IS_ENVP);
	ft_strcpy((*env)->value[i], name);
	ft_strlcat((*env)->value[i], "=", ft_strlen((*env)->value[i]));
	ft_strlcat((*env)->value[i], value, ft_strlen((*env)->value[i]));
	(*env)->value[i + 1] = NULL;
}

void	update_envp(t_envp **environment)
{
	int		i;
	int		level;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while ((*environment)->value[++i])
	{
		if (ft_strncmp((*environment)->value[i], "SHLVL=", 6) == 0)
		{
			level = ft_atoi((*environment)->value[i] + 6);
			tmp = ft_itoa(++level);
			if (!tmp)
				exit_free(*environment, ERROR, true, IS_ENVP);
			free((*environment)->value[i]);
			(*environment)->value[i] = ft_strjoin(ft_strdup("SHLVL="), tmp);
			if (!(*environment)->value[i])
				return (free(tmp), exit_free(*environment, ERROR, IS_ENVP));
			return (free(tmp));
		}
	}
	if (!(*environment)->value[i])
		set_exp(environment, "SHLVL", "1");
}
