#include "minishell.h"

void	close_all_fds(t_mini *data, t_cmd **cmd)
{
	if (data->prev_fd != -1 && data->prev_fd > 2)
		close(data->prev_fd);
	else if ((*cmd)->pipe_fd[0] != -1 && (*cmd)->pipe_fd[0] > 2)
		close((*cmd)->pipe_fd[0]);
	else if ((*cmd)->pipe_fd[1] != -1 && (*cmd)->pipe_fd[1] > 2)
		close((*cmd)->pipe_fd[1]);
	else if ((*cmd)->fd_in != -1 && (*cmd)->fd_in > 2)
		close((*cmd)->fd_in);
	else if ((*cmd)->fd_out != -1 && (*cmd)->fd_out > 2)
		close((*cmd)->fd_out);
}

static void	handler_redir(t_mini *data, t_cmd **cmd)
{
	if ((*cmd)->pipe_fd[0] != -1)
		close((*cmd)->pipe_fd[0]);
	if ((*cmd)->fd_in != -1)
	{
		dup2((*cmd)->fd_in, STDIN_FILENO);
		close((*cmd)->fd_in);
	}
	else if (data->prev_fd != -1)
	{
		dup2(data->prev_fd, STDIN_FILENO);
		close(data->prev_fd);
	}
	if ((*cmd)->fd_out != -1)
	{
		dup2((*cmd)->fd_out, STDOUT_FILENO);
		close((*cmd)->fd_out);
	}
	else if ((*cmd)->pipe_fd[1] != -1)
	{
		dup2((*cmd)->pipe_fd[1], STDOUT_FILENO);
		close((*cmd)->pipe_fd[1]);
	}
}

int	child_proccess(t_mini *data, t_cmd *cmd, char **envp)
{
		int	status;

		// if (cmd->fd_in == ERROR || cmd->fd_out == ERROR)
		// 	exit(ERROR); // leaks?
		// if (cmd->fd_in == 2 || cmd->fd_in == 1)
		// 	exit(cmd->fd_in); // ?? fd return like status; leaks?
		// if (cmd->fd_out == 2 || cmd->fd_out == 1)
		// 	exit(cmd->fd_out); // same
		handler_redir(data, &cmd);
		close_all_fds(data, &cmd);
		// if (is_builtin(cmd->token->value))
		// 	status = execute_builtin(data, cmd, envp);
		// else
		status = execute_command(cmd, envp);
		exit(status);
}
