#include "minishell.h"

int	wait_all(void)
{
	int		status;
	int		last_status;
	pid_t	pid;

	status = 0;
	last_status = 0;
	pid = -1;
	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
	return (update_status(last_status));
}

void	create_pipes(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) != 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return ((void)update_status(ERROR));
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

void	handler_redirections(int pipe_fd[2], int prev_fd, int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
	else if (fd_out != -1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
}