#include "minishell.h"

static char	*get_last_command(int argc, char **argv)
{
	char	*str;
	char	*tmp;

	if (!argv || !*argv)
		return (NULL);
	str = ft_strdup("_=");
	if (!str)
		return (NULL);
	if (argc < 2)
		return (str);
	argc--;
	while (argc >= 2)
	{
		while (is_option(argv[argc - 1]))
			argc--;
	}
	tmp = ft_strdup(argv[argc - 1]);
	if (!tmp)
		return (free(str), NULL);
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

char	**mini_envp(int argc, char **argv)
{
	char	**new;
	char	*tmp;

	new = ft_calloc(5, sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup("OLDPWD");
	if (!new[0])
		return (NULL);
	new[1] = ft_strdup("PWD=");
	if (!new[1])
		return (free(new[0]), free(new), NULL);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (free(new[0]), free(new[1]), free(new), NULL);
	new[1] = ft_strjoin(new[1], tmp);
	free(tmp);
	if (!new[1])
		return (free(new[0]), free(new), NULL);
	new[2] = get_last_command(argc, argv);
	if (!new[2])
		return (free(new[0]), free(new[1]), free(new), NULL);
	new[4] = NULL;
	return (new);
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
