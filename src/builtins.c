/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:22 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:22 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_mini *data, t_cmd *cmd)
{
	char	*builtin;

	if (!data || !cmd)
		return (update_status(ERROR));
	while (cmd->token && cmd->token->type != CMD)
		cmd->token = cmd->token->next;
	builtin = cmd->token->value;
	if (ft_strncmp(builtin, "echo", 5) == 0)
		return (update_status(ft_echo(cmd->token)));
	else if (ft_strncmp(builtin, "pwd", 4) == 0)
		return (update_status(ft_pwd(cmd->token, data->pwd)));
	else if (ft_strncmp(builtin, "cd", 3) == 0)
		return (update_status(ft_cd(data, cmd->token)));
	else if (ft_strncmp(builtin, "env", 4) == 0)
		return (update_status(ft_env(cmd->token, data->exp_vs)));
	else if (ft_strncmp(builtin, "export", 7) == 0)
		return (update_status(ft_export(data, cmd->token->next,
					cmd->token->value)));
	else if (ft_strncmp(builtin, "unset", 6) == 0)
		return (update_status(ft_unset(data, cmd->token)));
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (update_status(ft_exit(data, cmd->token)));
	return (OK);
}
