/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:58 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:46:10 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = token;
	while (last->next)
		last = last->next;
	return (last);
}

static int	get_redir_type(char *value)
{
	if (ft_strncmp(value, "<", ft_strlen(value)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(value, ">", ft_strlen(value)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(value, "<<", ft_strlen(value)) == 0)
		return (HEREDOC);
	else if (ft_strncmp(value, ">>", ft_strlen(value)) == 0)
		return (APPEND);
	return (ARG);
}

static bool	ok(char *value, bool check)
{
	if (!check && (!*value || *value == ' '))
		return (false);
	return (true);
}

int	get_type(t_cmd *cmd, t_token *token, char *value, bool check)
{
	t_token	*last;

	last = last_token(token);
	if (cmd && (is_validate_id(value) && ft_strchr(value, '='))
		&& (!has_type(token, CMD) && !has_type(token, REDIR_IN)
			&& !has_type(token, HEREDOC) && !has_type(token, REDIR_OUT)
			&& !has_type(token, APPEND)))
		return (VAR);
	else if ((!last || (last && last->type == VAR)) && !is_redir(value))
		return (CMD);
	else if (last && last->type == HEREDOC && !is_redir(value)
		&& ok(value, check))
		return (ENDOFFILE);
	else if (last && (last->type == APPEND || last->type == REDIR_IN
			|| last->type == REDIR_OUT) && !is_redir(value) && ok(value, check))
		return (FILE_PATH);
	else if (last && is_redir(last->value))
		return (ARG);
	else if ((ft_strncmp(value, "<", ft_strlen(value)) == 0 && !check)
		|| (ft_strncmp(value, ">", ft_strlen(value)) == 0 && !check)
		|| (ft_strncmp(value, "<<", ft_strlen(value)) == 0 && !check)
		|| (ft_strncmp(value, ">>", ft_strlen(value)) == 0 && !check))
		return (get_redir_type(value));
	else
		return (ARG);
}

void	set_new_token(t_token **new)
{
	free((*new)->value);
	(*new)->value = NULL;
	free(*new);
	*new = NULL;
}
