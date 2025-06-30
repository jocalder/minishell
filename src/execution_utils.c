#include "minishell.h"
void    close_father_fds(t_mini *data, t_cmd *cmd)
{
    if (cmd->fd_in != -1 && cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out != -1 && cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->pipe_fd[1] != -1 && cmd->pipe_fd[1] > 2)
			close(cmd->pipe_fd[1]);
		if (data->prev_fd != -1 && data->prev_fd > 2)
			close(data->prev_fd);
}