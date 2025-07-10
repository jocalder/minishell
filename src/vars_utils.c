#include "minishell.h"

char	*mini_getenv(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] == name[j] && envp[i][j] != '=')
			j++;
		if (envp[i][j] == '=' && name[j] == '\0')
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

int	count_str(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	set_new_var(char ***ptr, char *new_var, int i)
{
	char	**tmp;

	tmp = ft_realloc(ptr[0], sizeof(char *) * (i + 2));
	if (!tmp)
		return (update_status(ERROR));
	ptr[0] = tmp;
	ptr[0][i] = ft_strdup(new_var);
	if (!ptr[0][i])
		return (update_status(ERROR));
	ptr[0][i + 1] = NULL;
	return (OK);
}

int	set_existing_var(char ***ptr, char *var)
{
	int		i;

	if (!ft_strchr(var, '='))
		return (OK);
	i = 0;
	while ((*ptr)[i])
	{
		if (is_same_var((*ptr)[i], var))
		{
			free((*ptr)[i]);
			(*ptr)[i] = NULL;
			(*ptr)[i] = ft_strdup(var);
			if (!(*ptr)[i])
				return (update_status(ERROR));
			return (OK);
		}
		i++;
	}
	return (ERROR);
}

int	unset_var(char ***ptr, char *var, int len)
{
	int		i;
	int		j;
	char	**tmp;

	if (!ptr || !*ptr || !var)
		return (update_status(ERROR));
	tmp = ft_calloc(len, sizeof(char *));
	if (!tmp)
		return (update_status(ERROR));
	i = 0;
	j = 0;
	while ((*ptr)[i])
	{
		if (is_same_var((*ptr)[i], var) == true)
			free((*ptr)[i]);
		else
			tmp[j++] = (*ptr)[i];
		i++;
	}
	tmp[j] = NULL;
	free((*ptr));
	(*ptr) = tmp;
	return (OK);
}
