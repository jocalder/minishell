#include "minishell.h"

int open_heredoc(char *delimiter)
{
    int		pipe_fd[2];
    char	*line;
    int		large;
    pid_t	pid;

	line = NULL;
	large = ft_strlen(delimiter);
	if (pipe(pipe_fd) < 0)
		perror("pipe_heredoc failed");//errors and status
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while(1)
        {
        	write(1, "> ", 2);
        	line = get_next_line(0);
            if ((!line || ft_strncmp(line, delimiter, large) == 0)
				&& line[ft_strlen(delimiter)] == '\n')
            {
				free(line);
    			//handle errors and status
    			break ;
        	}
    		write(pipe_fd[1], line, ft_strlen(line));
    		free(line);
    	}
    	close(pipe_fd[1]);
		exit (0);
		//handle errors and status
	}
	else
	{
		//handle errors and status
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		return (pipe_fd[0]);
	}
	return (0);
}
