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
			return ((void)update_status(ERROR));
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}
