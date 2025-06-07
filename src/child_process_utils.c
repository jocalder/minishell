#include "minishell.h"

static int	redir_in(t_token *token)
{
	int		fd;

	fd = -1;
	while (token)
	{
		if (token->type == HEREDOC || token->type == REDIR_IN)
		{
			if (!token->next || !token->next->value)
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
				return (update_status(NOTFOUND));
			}
			if (fd != -1)
			close(fd);
			if (token->type == HEREDOC)
				fd = open_heredoc(token->next->value);
			else
				fd = open((token->next->value), O_RDONLY);
			if (fd < 0)
			{
				printf("minishell: %s: no such file or directory\n", token->next->value);
				return (update_status(NOTFOUND));//update errors to check
			}
		}
		token = token->next;
	}
	return (fd);
}

static int	redir_out(t_token *token)
{
	int		fd;

	fd = -1;
	while (token)
	{
		if (token->type == APPEND || token->type == REDIR_OUT)
		{
			if (!token->next || !token->next->value)
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
				return (update_status(NOTFOUND));
			}
			if (fd != -1)
				close(fd);
			if (token->type == APPEND)
				fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (update_status(NOTFOUND));//update errors to check my panita
		}
		token = token->next;
	}
	return (fd);
}

static void	close_all_fds(int pipe_fd[2], int prev_fd, int fd_in, int fd_out)
{
	if (prev_fd != -1)
		close(prev_fd);
	else if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	else if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	else if (fd_in != -1)
		close(fd_in);
	else if (fd_out != -1)
		close(fd_out);
}

void	child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp)
{
		int		fd_in;
		int		fd_out;

		fd_in = redir_in(cmd->token);
		fd_out = redir_out(cmd->token);
		if (fd_in == 127 || fd_out == 127)
			return ;
		if (fd_in != -1)
			dup2(fd_in, 0);
		else if (prev_fd != -1 && fd_in == -1)
			dup2(prev_fd, 0);
		if (pipe_fd[1] != -1 && fd_out == -1)
			dup2(pipe_fd[1], 1);
		else if (fd_out != -1)
			dup2(fd_out, 1);
		close_all_fds(pipe_fd, prev_fd, fd_in, fd_out);
		execute_command(cmd, envp);
		//Need exit in child proccess,
		//'cuz else still in it and not parent_process(minishell)
		exit(0);
}
