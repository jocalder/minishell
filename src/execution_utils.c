#include "minishell.h"

void	close_father_fds(t_mini *data, t_cmd **cmd)
{
	if ((*cmd)->next && (*cmd)->next->token && is_builtin((*cmd)->next->token))
		close((*cmd)->pipe_fd[1]);
	if ((*cmd)->fd_in != -1 && (*cmd)->fd_in > 2)
		close((*cmd)->fd_in);
	if ((*cmd)->fd_out != -1 && (*cmd)->fd_out > 2)
		close((*cmd)->fd_out);
	if ((*cmd)->pipe_fd[1] != -1 && (*cmd)->pipe_fd[1] > 2)
		close((*cmd)->pipe_fd[1]);
	if (data->prev_fd != -1 && data->prev_fd > 2)
		close(data->prev_fd);
}

void	handle_redirections(t_cmd **cmd)
{
	t_cmd 	*cur;
	t_token	*head;

	cur = *cmd;
	while (cur)
	{
		head = cur->token;
		while (cur->token)
		{
			if (cur->token->type == APPEND || cur->token->type == REDIR_OUT
			|| cur->token->type == HEREDOC || cur->token->type == REDIR_IN)
			{
				if (!cur->token->next || !cur->token->next->value)
				{
					if (cur->next)
						write(2, ERROR1, ft_strlen(ERROR1));
				}
			}
			cur->token = cur->token->next;
		}
		cur->token = head;
		cur = cur->next;
	}
	(*cmd)->fd_in = redir_in((*cmd), (*cmd)->token);
	(*cmd)->fd_out = redir_out((*cmd), (*cmd)->token);
}

int	check_fd_errors(t_cmd *cmd)
{
	return (cmd->fd_in == ERROR_FD || cmd->fd_out == ERROR_FD
		|| cmd->fd_in == SYNTAX || cmd->fd_out == SYNTAX
		|| g_status == CTRC);
}

int	handle_fd_errors(t_cmd **cmd)
{
	if ((*cmd)->fd_in == ERROR_FD || (*cmd)->fd_out == ERROR_FD)
		return (update_status(ERROR_FD));
	else if (g_status == CTRC)
		return (g_status);
	else
		return (update_status(SYNTAX));
}

void	clean_and_close(t_mini *data, t_cmd **cmd)
{
	close_father_fds(data, cmd);
	data->prev_fd = (*cmd)->pipe_fd[0];
	(*cmd)->pipe_fd[0] = -1;
	(*cmd)->pipe_fd[1] = -1;
	(*cmd) = (*cmd)->next;
}
