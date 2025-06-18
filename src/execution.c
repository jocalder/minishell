#include "minishell.h"

static int    wait_all(void)
{
    int 	status;
	int		last_status;
	pid_t	pid;

    status = 0;
	last_status = 0;
	pid = -1;
    while ((pid = wait(&status) > 0))
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
    return (update_status(last_status));
}

static void	create_pipes(t_cmd **cmd)
{
    if ((*cmd)->next)
	{
		if (pipe((*cmd)->pipe_fd) != 0)
			exit(ERROR); //leaks?
	}
	else
	{
		(*cmd)->pipe_fd[0] = -1;
		(*cmd)->pipe_fd[1] = -1;
	}
}

// Maybe could change prototype to static int redir_in(t_token *token, int *fd)
// Used int *fd to get de current fd, and int return of the funtion to return status
static int	redir_in(t_token *token)
{
	int		fd;
	int		i;

	fd = -1;
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC || token->type == REDIR_IN)
		{
			if (!token->next || !token->next->value)
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
				if (fd != -1)
					close(fd);
				return (SYNTAX);
			}
			if (fd != -1)
				close(fd);
			if (token->type == HEREDOC)
				fd = open_heredoc(token->next->value);
			else
				fd = open((token->next->value), O_RDONLY);
			if (fd < 0)
			{
				write(STDERR_FILENO, "minishell: ", 12);
				while (token->next->value[i])
					write(STDERR_FILENO, &token->next->value[i++], 1);
				write(STDERR_FILENO, ": no such file or directory\n", 29);
				return (ERROR);
			}
		}
		token = token->next;
	}
	return (fd);
}


// Maybe could change prototype to static int redir_out(t_token *token, int *fd)
// Used int *fd to get de current fd, and int return of the funtion to return status
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
				return (SYNTAX);
			}
			if (fd != -1)
				close(fd);
			if (token->type == APPEND)
				fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (ERROR);
		}
		token = token->next;
	}
	return (fd);
}

// prototype return int, but isn't used
int	handler_execution(t_mini *data, char **envp)
{
    t_cmd	*cmd;

	cmd = data->input->cmd;
	while (cmd)
	{
		create_pipes(&cmd);
		cmd->fd_in = redir_in(cmd->token);
		cmd->fd_out = redir_out(cmd->token);
		if (cmd->fd_in == ERROR || cmd->fd_out == ERROR)
		{
			if (cmd->fd_in != -1)
				close(cmd->fd_in);
			if (cmd->fd_out != -1)
				close(cmd->fd_out);
			cmd = cmd->next;
			continue ;
		}
		data->pid = fork();
		if (data->pid == 0)
			child_proccess(data, cmd, envp); // prototype return int, but isn't used
		// fds were closed in child_process, need close then here too?
		data->prev_fd = cmd->pipe_fd[0];
		cmd = cmd->next;
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	return (wait_all());
}
