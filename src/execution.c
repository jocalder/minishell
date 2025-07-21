/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:29 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/21 12:22:37 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_all(void)
{
	int		status;
	int		last_status;
	pid_t	pid;

	status = 0;
	last_status = 0;
	pid = -1;
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		pid = wait(&status);
		if (last_status == 141)
			last_status = 0;
	}
	return (update_status(last_status));
}

static void	create_pipes(t_cmd **cmd)
{
	if ((*cmd)->next)
	{
		if (pipe((*cmd)->pipe_fd) != 0)
		{
			close((*cmd)->pipe_fd[0]);
			close((*cmd)->pipe_fd[1]);
			exit(ERROR);
		}
	}
	else
	{
		(*cmd)->pipe_fd[0] = -1;
		(*cmd)->pipe_fd[1] = -1;
	}
}

int	redir_in(t_mini *data, t_cmd *cmd, t_token *tok)
{
	int	fd;

	fd = -1;
	while (tok)
	{
		if (tok->type == HEREDOC || tok->type == REDIR_IN)
		{
			if (!tok->next || (tok->next->type != 6 && tok->next->type != 7))
				return (redir_case(cmd, tok->next, &fd));
			if (fd != -1)
				close(fd);
			if (tok->type == HEREDOC)
			{
				fd = open_heredoc(data, &tok->next);
				if (g_status == CTRC)
					break ;
			}
			else
				fd = open((tok->next->value), O_RDONLY);
			if (fd < 0)
				return (write_error(tok), ERROR_FD);
		}
		tok = tok->next;
	}
	return (fd);
}

int	redir_out(t_cmd *cmd, t_token *token)
{
	int	fd;

	fd = -1;
	while (token)
	{
		if (token->type == APPEND || token->type == REDIR_OUT)
		{
			if (!token->next || !*token->next->value
				|| token->next->type != FILE_PATH)
				return (redir_case(cmd, token->next, &fd));
			if (fd != -1)
				close(fd);
			fd = open_fd(token);
			if (fd < 0)
				return (ERROR_FD);
		}
		token = token->next;
	}
	return (fd);
}

int	handler_execution(t_mini *data, t_cmd *cmd, char **envp)
{
	if (!cmd)
		return (g_status);
	wait_signal(1);
	w_parse_execution(cmd);
	while (cmd)
	{
		if (set_local_var(data, &cmd, cmd->token))
			continue ;
		handle_redirections(data, &cmd);
		if (check_fd_errors(cmd))
		{
			close_all_fds(data, &cmd);
			data->prev_fd = -1;
			return (handle_fd_errors(&cmd));
		}
		create_pipes(&cmd);
		if (is_builtin(cmd->token) && !cmd->next)
			return (builtin_and_redir(data, cmd));
		else
		{
			check_pid(data, cmd, envp);
			clean_and_close(data, &cmd);
		}
	}
	return (wait_all());
}
