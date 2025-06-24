#include "minishell.h"

static void	core_heredoc(char *line, char *delimiter, int large, int pipe_fd[2])
{
	close(pipe_fd[0]);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if ((!line || ft_strncmp(line, delimiter, large) == 0)
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			close(pipe_fd[1]);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	exit (0);
}

int	open_heredoc(char *delimiter)
{
	int				pipe_fd[2];
	char			*line;
	int				large;
	int				status;
	pid_t			pid;

	line = NULL;
	large = ft_strlen(delimiter);
	status = 0;
	if (!delimiter)
		return (-1);
	if (pipe(pipe_fd) < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), update_status(ERROR));
	pid = fork();
	if (pid < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
		core_heredoc(line, delimiter, large, pipe_fd);
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (-2);
		return (pipe_fd[0]);
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		return (-1);
	}
	return (pipe_fd[0]);
}
