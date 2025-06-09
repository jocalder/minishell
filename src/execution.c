#include "minishell.h"

static void    wait_all(void)
{
    int status;

    status = 0;
    while (wait(&status) > 0)
        ;
}

static void	create_pipes(t_cmd *cmd, int pipe_fd[2])
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

void    handler_execution(t_input *input, char **envp)
{
    t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	cmd = input->cmd;
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
	wait_all();
}
