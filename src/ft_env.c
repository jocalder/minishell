/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:38 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/22 14:24:47 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *data, t_token *token, char **exp_vs)
{
	char	*builtin;

	builtin = token->value;
	token = token->next;
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG)
	{
		if (is_option(token->value))
			w_builtin_usage(builtin, token->value);
		else
			write(STDERR_FILENO, "minishell: env: too many arguments\n", 36);
		return (update_status(SYNTAX));
	}
	update_underscore(data);
	while (*exp_vs)
	{
		if (ft_strchr(*exp_vs, '='))
		{
			write(STDOUT_FILENO, *exp_vs, ft_strlen(*exp_vs));
			write(STDOUT_FILENO, "\n", 1);
		}
		exp_vs++;
	}
	return (update_status(OK));
}
