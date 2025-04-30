#include "minishell.h"

int	count_pipes(t_cmd *cmd)
{
    t_cmd	*temp;
    int		count;

    count = 0;
    temp = cmd;
    while (temp && temp->next)
    {
		count++;
    	temp = temp->next;
    }
    return (count);
}

int	**create_pipefds(int n)
{
	int		**fds;
	int		i;

	fds = ft_calloc(n , sizeof(int *));
	i = 0;
	while (i < n)
	{
		fds[i] = ft_calloc(2, sizeof(int *))
		if (pipe(fds[i]) != 0)
			perror("error pipesfds")
		i++;
	}
	return (fds);
}
void	execute_pipes(t_cmd *cmd, char *envp)
{
	int		**pipe_fds;

	cmd->pipes = count_pipes(cmd);
	pipes_fds = create_pipefds(cmd->pipes);
}

void	execute_command(t_cmd *cmd, char **envp)
{

}
char	*find_command_path(char *cmd, char **envp)
{
    char	**directories;
    char	*full_path;
    char	*path;
    int		i;

    i = 0;
    while (envp[i] && !ft_strncmp(envp[i], "PATH=", 5))
        i++;
    directories = ft_split(envp[i], ':');
    i = 0;
    while (directories[i])
    {
        path = ft_strjoin(directories[i], '/');
        full_path = ft_strjoin(path, cmd);
        free(path);
        if (access(full_path, F_OK) == 0)
            return (full_path);//falta funcion para liberar
        free(full_path);
    }
    return (NULL);//function to free
}
