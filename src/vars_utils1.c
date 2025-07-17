/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:16:03 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:16:04 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	tmp = ft_realloc(*ptr, sizeof(char *) * (i + 2));
	if (!tmp)
		return (update_status(ERROR));
	*ptr = tmp;
	(*ptr)[i] = ft_strdup(new_var);
	if (!(*ptr)[i])
		return (update_status(ERROR));
	(*ptr)[i + 1] = NULL;
	return (OK);
}

int	set_existing_var(char ***ptr, char *var)
{
	int	i;

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
