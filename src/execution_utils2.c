#include "minishell.h"

void    wait_all(void)
{
    int status;

    status = 0;
    while (wait(&status) > 0)
        ;
}

void    create_pipes(t_cmd *cmd, int pipe_fd[2])
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
}