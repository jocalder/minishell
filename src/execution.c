#include "minishell.h"

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

		fd_in = //function to handle the redir_in that return (-1) if doesn´t exist the redir;
		fd_out = //function to handle the redir_out that return (-1) if doesn´t exist the redir;

		if (fd_in != -1)
			dup2(fd_in, 0);
		else if (prev_fd[0] != -1 && fd_in == -1)
			dup2(prev_fd[0], 0);
		if (pipe_fd[1] != -1 && fd_out == -1)
			dup2(pipe_fd[1], 1);
		else if (fd_out != -1)
			dup2(fd_out, 1);
		close_all_fds(pipe_fd, prev_fd, fd_in, fd_out); //function to close all the open fds
		execute_command(cmd, envp);
}
