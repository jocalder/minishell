/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:14:30 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:14:33 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_spacetab(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

bool	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	is_redir(char *str)
{
	if (!str || !*str)
		return (false);
	if (ft_strncmp(str, "<<<", 3) == 0 || ft_strncmp(str, ">>>", 3) == 0
		|| ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0
		|| ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
		return (true);
	return (false);
}

bool	is_special(char *str)
{
	size_t	len;

	if (!str || !*str)
		return (false);
	len = 0;
	if (str[len] == '$'
		&& (str[len + 1] && !is_spacetab(str[len + 1])))
		return (true);
	return (false);
}

bool	is_supported(char *start, bool flag)
{
	size_t	end;
	char	c;

	if (!start || !*start || flag)
		return (true);
	c = start[0];
	end = ft_strlen(start) - 1;
	while (end > 0 && is_spacetab((start)[end]))
		end--;
	if ((ft_strncmp(start, "&&", 2) == 0) || (ft_strncmp(start, "||", 2) == 0)
		|| c == ';' || c == '&' || c == '\\' || c == '`'
		|| c == '(' || c == ')' || start[end] == '(' || start[end] == ')'
		|| (c == '[' && (end > 0 && !is_spacetab(start[1]))))
		return (false);
	return (true);
}
