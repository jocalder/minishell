#include "minishell.h"

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
	ptr[0][i] = ft_strdup(new_var);
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
