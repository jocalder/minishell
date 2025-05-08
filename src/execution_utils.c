#include "minishell.h"

static void	free_directories(char **directories)
{
	int		i;

	i = 0;
	while (directories[i])
	{
		free(directories[i]);
		i++;
	}
	free(directories);
}

static int	count_args(t_token *token)
{
	int		count;

	count = 0;
	while (token)
	{
		if (token->type == CMD || token->type == OPC)
			count++;
		token = token->next;
	}
	return (count);
}
char	*find_command_path(char	*command, char **envp)//changes with the structures
{
	char	**directories;
	char	*full_path;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	directories = ft_split(envp[i + 5], ':');
	i = -1;
	while (directories[++i])
	{
		path = ft_strjoin(directories[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path, free_directories(directories));
		free(full_path);
	}
	free_directories(directories);
	free(full_path);
	return (NULL);
}

char	*build_full_command(t_token *token)
{
	int		count;
	char	*args;
	int		i;

	i = 0;
	count = count_args(token);
	args = malloc(sizeof(char *) * (count + 1));
	while (token)
	{
		if (token->type == CMD || token->type == OPC)
		{
			args[i] = ft_strdup(token->value);
			i++;
		}
		token = token->next;
	}
	args[i] = NULL;
	return (args);

}

