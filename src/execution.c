#include "minishell.h"

static void	close_all_fds(int pipe_fd, int prev_fd[2], int fd_in, int fd_out)
{
	if (pipe_fd != -1)
		close(pipe_fd);
	else if (prev_fd[0] != -1)
		close(prev_fd[0]);
	else if (prev_fd[1] != -1)
		close(prev_fd[1])
	else if (fd_in != -1)
		close(fd_in);
	else if (fd_out != -1)
		close(fd_out);
}

void    handle_execution(t_mini *data, char *envp)
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
			if (!pipe(pipe_fd))
				return (NULL);//message error or handle errors, status
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
	//function wait to handle the father proccess;
}

void	ft_child_proccess(int *pipe_fd, int *prev_fd, t_cmd *cmd, char **envp)
{
		int		fd_in;
		int		fd_out;

		fd_in = redir_in(cmd->token);
		fd_out = redir_out(cmd->token);

		if (fd_in != -1)
			dup2(fd_in, 0);
		else if (prev_fd[0] != -1 && fd_in == -1)
			dup2(prev_fd[0], 0);
		if (pipe_fd[1] != -1 && fd_out == -1)
			dup2(pipe_fd[1], 1);
		else if (fd_out != -1)
			dup2(fd_out, 1);
		close_all_fds(pipe_fd, prev_fd, fd_in, fd_out);
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
			fd = open_heredoc(token->next->value);
			if (fd < 0)
				//function to handle errors
			return (fd);
		}
		if (toke->type == REDIR_IN)
		{
			fd = open((token->next->value), O_RDONLY);
			if (fd < 0)
				//function to handle errors
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
			fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				//status and handle errors
			return (fd);
		}
		if (token->type == REDIR_OUT)
		{
			fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				//function to handle errors and status
			return (fd);
		}
		token = token->next;
	}
	return (fd);
}
