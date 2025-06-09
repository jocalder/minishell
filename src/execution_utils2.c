#include "minishell.h"

int	wait_all(void)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = -1;
	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (update_status(status));
		else if (WIFSIGNALED(status))
			return (update_status(128 + WTERMSIG(status)));
	}
	return (update_status(OK));
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
