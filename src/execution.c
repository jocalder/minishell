#include "minishell.h"

static void	close_all_fds(int pipe_fd[2], int prev_fd, int fd_in, int fd_out)
{
	if (prev_fd != -1)
		close(prev_fd);
	else if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	else if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	else if (fd_in != -1)
		close(fd_in);
	else if (fd_out != -1)
		close(fd_out);
}

void    handle_execution(t_mini *data, char **envp)
{
    t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	cmd = data->input->cmd;
	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipe_fd) != 0)
				perror("pipe failed");//handle errors, status
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		pid = fork();
		if (pid == 0)
			ft_child_proccess(pipe_fd, prev_fd, cmd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	wait_all();
}

void	ft_child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp)
{
		int		fd_in;
		int		fd_out;

		fd_in = redir_in(cmd->token);
		fd_out = redir_out(cmd->token);
		if (fd_in != -1)
			dup2(fd_in, 0);
		else if (prev_fd != -1 && fd_in == -1)
			dup2(prev_fd, 0);
		if (pipe_fd[1] != -1 && fd_out == -1)
			dup2(pipe_fd[1], 1);
		else if (fd_out != -1)
			dup2(fd_out, 1);
		close_all_fds(pipe_fd, prev_fd, fd_in, fd_out);
		//if (is_builtin(cmd->token->value))
		//	execute_builtin(cmd, envp);
		//else
		execute_command(cmd, envp);
}

int	redir_in(t_token *token)
{
	int		fd;

	fd = -1;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (fd != -1)
				close(fd);
			fd = open_heredoc(token->next->value);
			if (fd < 0)
				perror("fd: open_heredoc failed");//handle errors and status
		}
		if (token->type == REDIR_IN)
		{
			if (fd != -1)
				close(fd);
			fd = open((token->next->value), O_RDONLY);
			if (fd < 0)
				perror("minishell: token->value: No such file or directory");//handle errors and status
			if (token->next->next == NULL && token->next->type == FILE_PATH)
				return (fd);
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
		if (token->type == APPEND)
		{
			if (fd != -1)
				close(fd);
			fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				perror("minishell: token->value: no such file or directory");//handle errors and status
			if (token->next->next == NULL && token->next->type == FILE_PATH)
				return (fd);
		}
		if (token->type == REDIR_OUT)
		{
			if (fd != -1)
				close(fd);
			fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				perror("minishell: token->value: no such file or directory");//handle errors and status
			if (token->next->next == NULL && token->next->type == FILE_PATH)
				return (fd);
		}
		token = token->next;
	}
	return (fd);
}
