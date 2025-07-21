/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:23 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:23 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds(t_mini *data, t_cmd **cmd)
{
	if (data->prev_fd != -1 && data->prev_fd > 2)
		close(data->prev_fd);
	if ((*cmd)->pipe_fd[0] != -1 && (*cmd)->pipe_fd[0] > 2)
		close((*cmd)->pipe_fd[0]);
	if ((*cmd)->pipe_fd[1] != -1 && (*cmd)->pipe_fd[1] > 2)
		close((*cmd)->pipe_fd[1]);
	if ((*cmd)->fd_in != -1 && (*cmd)->fd_in > 2)
		close((*cmd)->fd_in);
	if ((*cmd)->fd_out != -1 && (*cmd)->fd_out > 2)
		close((*cmd)->fd_out);
}

void	handler_dup(t_mini *data, t_cmd **cmd)
{
	if ((*cmd)->pipe_fd[0] != -1)
		close((*cmd)->pipe_fd[0]);
	if ((*cmd)->fd_in != -1)
	{
		dup2((*cmd)->fd_in, STDIN_FILENO);
		close((*cmd)->fd_in);
	}
	else if (data->prev_fd != -1)
	{
		dup2(data->prev_fd, STDIN_FILENO);
		close(data->prev_fd);
	}
	if ((*cmd)->fd_out != -1)
	{
		dup2((*cmd)->fd_out, STDOUT_FILENO);
		close((*cmd)->fd_out);
	}
	else if ((*cmd)->pipe_fd[1] != -1)
	{
		dup2((*cmd)->pipe_fd[1], STDOUT_FILENO);
		close((*cmd)->pipe_fd[1]);
	}
}

void	child_proccess(t_mini *data, t_cmd *cmd, char **envp)
{
	int	status;

	status = 0;
	handler_dup(data, &cmd);
	close_all_fds(data, &cmd);
	if (is_builtin(cmd->token))
		status = execute_builtin(data, cmd);
	else
		status = execute_command(cmd, envp);
	exit_free(data, update_status(status));
}
