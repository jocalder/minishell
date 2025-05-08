#include "minishell.h"

char	*find_command_path(char	*command, char **envp)//changes with the structures
{
	char	**directories;
	char	*full_path;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	directories = ft_split(envp[i] + 5, ':');
	i = -1;
	while (directories[++i])
	{
		path = ft_strjoin(directories[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path, free(directories));
		free(full_path);
	}
	free(directories);
	return (NULL);
}

