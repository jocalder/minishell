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

	tmp = ft_calloc(len, sizeof(char *));
	if (!tmp)
		return (update_status(ERROR));
	i = 0;
	j = 0;
	while (ptr[0][i])
	{
		if (is_same_var(ptr[0][i], var) == true)
			free(ptr[0][i]);
		else
			tmp[j++] = ptr[0][i];
		i++;
	}
	tmp[j] = NULL;
	free_array(ptr[0], -1);
	ptr[0] = tmp;
	return (OK);
}
