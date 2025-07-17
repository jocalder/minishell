#include "minishell.h"

static void	core_heredoc(t_mini *data, t_token *token, int pipe_fd[2])
{
	char	*line;
	size_t	len;

	len = ft_strlen(token->value);
	wait_signal(2, pipe_fd);
	close(pipe_fd[0]);
	while (isatty(STDIN_FILENO))
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (((!line
					|| (!*line || (ft_strncmp(line, token->value, len) == 0
							&& line[len] == '\n')))))
		{
			if (line)
				free(line);
			break ;
		}
		if (!token->flag)
			line = expand_content(data, line, NULL);
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	exit (0);
}

int	open_heredoc(t_mini *data, t_token *token)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(pipe_fd) < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), update_status(ERROR));
	pid = fork();
	if (pid < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
		core_heredoc(data, token, pipe_fd);
	if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (close(pipe_fd[0]), -1);
		return (pipe_fd[0]);
	}
	return (-1);
}
