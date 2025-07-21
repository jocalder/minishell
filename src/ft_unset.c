/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:46 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:47 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_mini *data, t_token *token)
{
	char	*builtin;

	builtin = token->value;
	token = token->next;
	if (token && token->type == ARG && is_option(token->value))
		return (w_builtin_usage(builtin, token->value), update_status(SYNTAX));
	update_status(OK);
	while (token && token->type == ARG)
	{
		if (!is_validate_id(token->value) || ft_strchr(token->value, '='))
		{
			update_status(ERROR_FD);
			w_invalid_identifier(builtin, token->value);
			token = token->next;
			continue ;
		}
		if (is_existing_var(data->exp_vs, token->value))
			unset_var(&data->exp_vs, token->value,
				count_str(data->exp_vs));
		if (is_existing_var(data->vars, token->value))
			unset_var(&data->vars, token->value, count_str(data->vars));
		token = token->next;
	}
	return (g_status);
}
