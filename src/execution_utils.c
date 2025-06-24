#include "minishell.h"

static char	*absolute_path(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (access(cmd->token->value, F_OK) == 0)
		return (cmd->token->value);
	else
	{
		write(2, "minishell: ", 11);
		while (cmd->token->value[i])
			write(2, &cmd->token->value[i++], 1);
		write(2, ": no such file or directory\n", 28);
		return (cmd->token->value);
	}
}

static int	count_args(t_token *token)
{
	int		count;

	count = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
			count++;
		token = token->next;
	}
	return (count);
}

static char	*find_command_path(char	*command, char **envp, t_cmd *cmd)
{
	char	**directories;
	char	*full_path;
	char	*path;
	int		i;

	i = 0;
	if (cmd && cmd->token && cmd->token->value &&
		(ft_strncmp(cmd->token->value, "/bin/", 5) == 0
		|| ft_strncmp(cmd->token->value, "./", 2) == 0))
		return (absolute_path(cmd));
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	directories = ft_split(envp[i], ':');
	i = -1;
	while (directories[++i])
	{
		path = ft_strjoin(directories[i], "/");
		full_path = ft_strjoin(path, command);
		if (access(full_path, F_OK) == 0)
			return (free(directories), full_path);
		free(full_path);
	}
	free(directories);
	return (NULL);
}

static char	**build_full_command(t_token *token)
{
	int		count;
	char	**args;
	int		i;

	i = 0;
	count = count_args(token);
	args = malloc(sizeof(char *) * (count + 1));
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			args[i] = ft_strdup(token->value);
			i++;
		}
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

int	execute_command(t_cmd *cmd, char **envp)
{
	char	**command;
	char	*path;
	int		i;
	int		fd;

	i = 0;
	fd = 3;
	command = build_full_command(cmd->token);
	path = find_command_path(command[0], envp, cmd);
	if (!path)
	{
		write(2, "minishell: ", 11);
		while (command[0][i])
			write(2, &command[0][i++], 1); 
		write(2, ": command not found\n", 20);
		free_array(command);
		return (NOTFOUND);
	}
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	execve(path, command, envp);
	free_array(command);
	return (ERROR);
}
