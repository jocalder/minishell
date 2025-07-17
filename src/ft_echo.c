/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:37 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:38 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	bool	suppress_newline;

	suppress_newline = false;
	token = token->next;
	while (token && token->type != ARG)
		token = token->next;
	while (token && (token->type == ARG
			&& ft_strncmp(token->value, "-n", 2) == 0))
	{
		suppress_newline = true;
		token = token->next;
	}
	while (token && token->type == ARG)
	{
		write(STDOUT_FILENO, token->value, ft_strlen(token->value));
		if (token->next && token->next->type == ARG)
			write(STDOUT_FILENO, " ", 1);
		token = token->next;
	}
	if (!suppress_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (update_status(OK));
}
