/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:27 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:22:27 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(t_token *token)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "minishell: ", 12);
	while (token->next->value[i])
		write(STDERR_FILENO, &token->next->value[i++], 1);
	write(STDERR_FILENO, ": no such file or directory\n", 29);
}

int	open_fd(t_token *token)
{
	int	fd;

	fd = -1;
	if (token->type == APPEND)
		fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}

void	check_pid(t_mini *data, t_cmd *cmd, char **envp)
{
	data->pid = fork();
	if (data->pid == -1)
		update_status(ERROR);
	if (data->pid == 0)
		child_proccess(data, cmd, envp);
}

int	builtin_and_redir(t_mini *data, t_cmd *cmd)
{
	data->stdin = dup(0);
	data->stdout = dup(1);
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	close_all_fds(data, &cmd);
	execute_builtin(data, cmd);
	dup2(data->stdin, STDIN_FILENO);
	close(data->stdin);
	dup2(data->stdout, STDOUT_FILENO);
	close(data->stdout);
	if (data->prev_fd != -1 && data->prev_fd > 2)
		data->prev_fd = -1;
	return (g_status);
}

int	redir_case(t_cmd *cmd, t_token *next, int *fd)
{
	if (*fd != -1)
		close(*fd);
	if (next && (*next->value != '\0' && *next->value != ' '))
		w_unexpected_redir(next->value);
	else if (next && (!*next->value || *next->value == ' '))
	{
		w_not_such(next->value);
		return (ERROR_FD);
	}
	else if (!cmd->next)
		write(STDERR_FILENO, ERROR4, ft_strlen(ERROR4));
	return (SYNTAX);
}
