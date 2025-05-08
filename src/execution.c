#include "minishell.h"

void    handle_fds(t_mini *data, char *envp)
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
				return (NULL);//message error or handle errors
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
	int	infile;

	infile = 0;
	if (INFILE)
		infile = open(token->value, O_RDONLY)
	
}