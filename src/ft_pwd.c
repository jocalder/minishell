/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:44 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:45 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_token *token, char *pwd)
{
	char	*value;
	char	*builtin;

	value = NULL;
	builtin = token->value;
	token = token->next;
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG)
	{
		value = token->value;
		if (is_option(value))
		{
			w_builtin_usage(builtin, value);
			return (update_status(SYNTAX));
		}
	}
	if (!pwd)
		return ((void)write(STDERR_FILENO,
				"minishell: pwd: cannot get the current directory\n",
				50), update_status(ERROR));
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (update_status(OK));
}
