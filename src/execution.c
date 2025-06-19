#include "minishell.h"

static void	close_fds(int pipe_fd[2], int prev_fd, int fd_in, int fd_out)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
}

int	handle_execution(t_mini *data, char **envp)
{
	t_cmd				*cmd;
	int					pipe_fd[2];
	int					prev_fd;
	pid_t				pid;

	cmd = data->input->cmd;
	prev_fd = -1;
	while (cmd)
	{
		create_pipes(cmd, pipe_fd);
		cmd->fd_in = redir_in(cmd->token);
		cmd->fd_out = redir_out(cmd->token);
		printf("fd_in: %d\n", cmd->fd_in);
		if (cmd->fd_in == ERROR || cmd->fd_out == ERROR
			|| cmd->fd_in == SINTAX || cmd->fd_out == SINTAX)
		{
			close_fds(pipe_fd, prev_fd, cmd->fd_in, cmd->fd_out);
			prev_fd = -1;
			if (!cmd->next)
			{
				if (cmd->fd_in == ERROR || cmd->fd_out == ERROR)
					return (update_status(1));
				else
					return (update_status(2));
			}
			cmd = cmd->next;
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			close_fds(pipe_fd, prev_fd, cmd->fd_in, cmd->fd_out);
			return (update_status(1));
		}
		if (pid == 0)
			child_proccess(pipe_fd, prev_fd, cmd, envp);
		close_fds(pipe_fd, prev_fd, cmd->fd_in, cmd->fd_out);
		prev_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (wait_all());
}

int	child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp)
{
	int	status;

	if (cmd->fd_in == SINTAX || cmd->fd_in == ERROR)
		exit(cmd->fd_in);
	if (cmd->fd_out == SINTAX || cmd->fd_out == ERROR)
		exit(cmd->fd_out);
	handler_redirections(pipe_fd, prev_fd, cmd->fd_in, cmd->fd_out);
	close_fds(pipe_fd, prev_fd, cmd->fd_in, cmd->fd_out);
	status = execute_command(cmd, envp);
	exit(status);
}

int	redir_in(t_token *token)
{
	int		fd;
	int		i;

	i = 0;
	fd = -1;
	while (token)
	{
		if (token->type == HEREDOC || token->type == REDIR_IN)
		{
			if (!token->next || !token->next->value)
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
				if (fd != -1)
					close(fd);
				return (SINTAX);
			}
			if (fd != -1)
				close(fd);
			if (token->type == HEREDOC)
				fd = open_heredoc(token->next->value);
			else
				fd = open((token->next->value), O_RDONLY);
			if (fd < 0)
			{
				write(2, "minishell: ", 11);
				while (token->next->value[i])
					write(2, &token->next->value[i++], 1);
				write(2, ": no such file or directory\n", 29);
				return (ERROR);
			}
		}
		token = token->next;
	}
	return (fd);
}

int	redir_out(t_token *token)
{
	int		fd;

	fd = -1;
	while (token)
	{
		if (token->type == APPEND || token->type == REDIR_OUT)
		{
			if (!token->next || !token->next->value)
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
				return (SINTAX);
			}
			if (fd != -1)
				close(fd);
			if (token->type == APPEND)
				fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (ERROR);
		}
		token = token->next;
	}
	return (fd);
}
