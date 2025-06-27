#include "minishell.h"

static void	core_heredoc(char *line,char *delimiter,int large,int pipe_fd[2])
{
	wait_signal(2);
	close(pipe_fd[0]);
	while(1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if ((!line || ft_strncmp(line, delimiter, large) == 0)
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	exit (0);
}

int open_heredoc(char *delimiter)
{
    int		pipe_fd[2];
    char	*line;
    int		large;
    pid_t	pid;
	int		status;
	void	(*sig)(int);

	status = 0;
	line = NULL;
	large = ft_strlen(delimiter);
	if (pipe(pipe_fd) < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), update_status(ERROR));
	sig = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		signal(SIGINT, sig);
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		core_heredoc(line, delimiter, large, pipe_fd);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(-1, &status, 0);
		signal(SIGINT, sig);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
    		close(pipe_fd[0]);
    		write(1, "\n", 2);
    		return (HEREDOC_CTRLC);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (close(pipe_fd[0]), -1);
		return (pipe_fd[0]);
	}
	return (-1);
}
