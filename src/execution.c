#include "minishell.h"

static void	close_all_fds(int pipe_fd[2], int prev_fd, int fd_in, int fd_out)
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
		pid = fork();
		if (pid == 0)
			child_proccess(pipe_fd, prev_fd, cmd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (wait_all());
}

int	child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	status;

	fd_in = redir_in(cmd->token);
	fd_out = redir_out(cmd->token);
	if (fd_in == 2 || fd_out == 2)
		exit(SINTAX);
	else if (fd_in == 1 || fd_out == 1)
		exit(ERROR);
	handler_redirections(pipe_fd, prev_fd, fd_in, fd_out);
	close_all_fds(pipe_fd, prev_fd, fd_in, fd_out);
	status = execute_command(cmd, envp);
	exit(status);
}

int	redir_in(t_token *token)
{
	int		fd;

	fd = -1;
	while (token)
	{
		if (token->type == HEREDOC || token->type == REDIR_IN)
		{
			if (!token->next || !token->next->value)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
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
				printf("minishell: %s: no such file or directory\n", token->next->value);
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
				printf("minishell: syntax error near unexpected token `newline'\n");
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
