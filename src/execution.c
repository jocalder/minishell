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

int	redir_in(t_token *token)
{
	int	fd;

	fd = -1;
	while (token)
	{
		if (token->type == HEREDOC || token->type == REDIR_IN)
		{
			if (!token->next || !token->next->value)
			{
				if (fd != -1)
					close(fd);
				return (write(2, ERROR4, ft_strlen(ERROR4)), SYNTAX);
			}
			if (fd != -1)
				close(fd);
			if (token->type == HEREDOC)
				fd = open_heredoc(token->next->value);
			else
				fd = open((token->next->value), O_RDONLY);
			if (fd < 0)
				return (write_error(token), ERROR_FD);
		}
		token = token->next;
	}
	return (fd);
}

int	redir_out(t_token *token)
{
	int	fd;

	fd = -1;
	while (token)
	{
		if (token->type == APPEND || token->type == REDIR_OUT)
		{
			if (!token->next || !token->next->value)
			{
				write(STDERR_FILENO, ERROR4, ft_strlen(ERROR4));
				return (SYNTAX);
			}
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
	while (cmd)
	{
		wait_signal(1);
		handle_redirections(&cmd);
		if (check_fd_errors(cmd))
		{
			close_all_fds(data, &cmd);
			data->prev_fd = -1;
			if (!cmd->next)
				return (handle_fd_errors(&cmd));
			cmd = cmd->next;
			continue ;
		}
		create_pipes(&cmd);
		if (is_builtin(cmd->token) && !cmd->next)
		{
			handler_redir(data, &cmd);
			close_fds_builtin(data, &cmd);
			//close_father_fds(data, &cmd);
			execute_builtin(data, cmd);
			return (g_status);
		}
		else
		{
			data->pid = fork();
			check_pid(data, cmd, envp);
			clean_and_close(data, &cmd);
		}
	}
	return (wait_all());
}
