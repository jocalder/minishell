/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:12 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:13 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_token *token)
{
	char	*value;

	if (!token || !token->value)
		return (false);
	while (token && token->type != CMD)
		token = token->next;
	if (!token)
		return (false);
	value = token->value;
	if (ft_strncmp(value, "echo", 5) == 0
		|| ft_strncmp(value, "pwd", 4) == 0
		|| ft_strncmp(value, "cd", 3) == 0
		|| ft_strncmp(value, "export", 7) == 0
		|| ft_strncmp(value, "unset", 6) == 0
		|| ft_strncmp(value, "env", 4) == 0
		|| ft_strncmp(value, "exit", 5) == 0)
		return (true);
	return (false);
}

bool	is_option(char *value)
{
	if ((ft_strncmp(value, "--", 2) == 0 && ft_strlen(value) > 2)
		|| (ft_strncmp(value, "-", 1) == 0 && ft_strlen(value) > 1))
		return (true);
	return (false);
}

bool	is_validate_id(char *id)
{
	int	i;

	if (!id || !*id)
		return (false);
	i = 0;
	if (!ft_isalpha(id[i]) && id[i] != '_')
		return (false);
	i = 1;
	while (id[i] && id[i] != '=')
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_existing_var(char **ptr, char *var)
{
	int		i;

	if (!ptr || !*ptr)
		return (false);
	i = 0;
	while (ptr[i])
	{
		if (is_same_var(ptr[i], var))
			return (true);
		i++;
	}
	return (false);
}

bool	is_same_var(char *compared, char *var)
{
	size_t	len_compared;
	size_t	len_var;
	size_t	len;
	char	*tmp;

	tmp = ft_strchr(compared, '=');
	len_compared = ft_strlen(compared) - ft_strlen(tmp);
	tmp = NULL;
	tmp = ft_strchr(var, '=');
	len_var = ft_strlen(var) - ft_strlen(tmp);
	if (len_compared < len_var)
		len = len_var;
	else
		len = len_compared;
	if (ft_strncmp(compared, var, len) == 0)
		return (true);
	else
		return (false);
}
