#include "minishell.h"

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

void    handle_execution(t_mini *data, char **envp)
{
    t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	cmd = data->input->cmd;
	prev_fd = -1;
	while (cmd)
	{
		create_pipes(cmd, pipe_fd);
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
	wait_all();
}

void	ft_child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp)
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
		//status when the execution is successful
}

int	redir_in(t_token *token)
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

int	redir_out(t_token *token)
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
