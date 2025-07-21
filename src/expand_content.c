/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:31 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/21 12:34:07 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_special_var(t_mini *data, char *name)
{
	if (!name || !*name)
		return (ft_strdup(""));
	if (*name == '?')
		return (ft_itoa(g_status));
	return (ft_itoa(data->pid));
}

static char	*get_env_var(t_mini *data, char *name)
{
	char	*var;

	if (!name)
		return (ft_strdup(""));
	var = ft_strdup(mini_getenv(name, data->exp_vs));
	if (!var)
	{
		var = ft_strdup(mini_getenv(name, data->vars));
		if (!var)
		{
			var = ft_strdup("");
			if (!var)
			{
				update_status(ERROR);
				return (free(name), NULL);
			}
		}
	}
	return (free(name), var);
}

static char	*handler_expand(t_mini *data, char *value, size_t *len)
{
	char	*new_value;

	if (!value)
		return (ft_strdup(""));
	new_value = NULL;
	if (value[*len] == '?' || value[*len] == '$')
	{
		new_value = get_special_var(data, value);
		(*len)++;
	}
	else if (ft_isalpha(value[*len]) || (value[*len] == '_'))
	{
		while (value[*len]
			&& (value[*len] != '$' && value[*len] != '=' && !is_quote(value[*len])
				&& !is_spacetab(value[*len])))
			(*len)++;
		new_value = get_env_var(data, ft_substr(value, 0, *len));
	}
	else
	{
		(*len)++;
		return (ft_strdup(""));
	}
	return (new_value);
}

char	*expand_content(t_mini *data, char *value, t_token *last)
{
	char	*new_value;
	char	*start;
	char	*tmp;
	size_t	len;

	if (!value)
		return (ft_strdup(""));
	if (last && last->type == HEREDOC)
		return (value);
	new_value = ft_strdup("");
	start = value;
	while (*start)
	{
		tmp = NULL;
		len = 0;
		if (*start == '$' && (start[len + 1]
				&& (!is_spacetab(start[len + 1]) && start[len + 1] != '=')))
			tmp = handler_expand(data, ++start, &len);
		else
			tmp = ft_substr(start, 0, ++len);
		start += len;
		new_value = ft_strjoin(new_value, tmp);
		free(tmp);
	}
	return (free(value), new_value);
}
