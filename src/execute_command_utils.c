#include "minishell.h"

static char	*absolute_path(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (access(cmd->token->value, F_OK) == 0)
		return (cmd->token->value);
	else
	{
		write(STDERR_FILENO, "minishell: ", 12);
		while (cmd->token->next->value[i])
			write(STDERR_FILENO, &cmd->token->next->value[i++], 1);
		write(STDERR_FILENO, ": no such file or directory\n", 29);
		return (cmd->token->value);
	}
}

static char	*find_command_path(char	*command, char **envp, t_cmd *cmd)
{
	char	**directories;
	char	*full_path;
	char	*path;
	int		i;

	i = 0;
	if (cmd && cmd->token && cmd->token->value
		&& (ft_strncmp(cmd->token->value, "/bin/", 5) == 0
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
			return (free_array(directories, i), full_path);
		free(full_path);
	}
	free_array(directories, i);
	return (NULL);
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
			args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

int	execute_command(t_cmd *cmd, char **envp)
{
	char	**command;
	char	*path;
	t_token	*cur;
	int		i;
	
	i = 0;
	command = build_full_command(cmd->token);
	path = find_command_path(command[0], envp, cmd);
	if (!path)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		while(command[0][i])
			write(STDERR_FILENO, &command[0][i++], 1);
		write(STDERR_FILENO, ": command not found\n", 21);
		free_array(command, -1);
		return (NOTFOUND);
	}
	cur = cmd->token;
	while (path && cur)
	{
		if (cur->type == ARG && !cur->flag && !is_supported(cur->value))
			return (w_unsupported(cur->value), update_status(SYNTAX));
		cur = cur->next;
	}
	// if (execve(path, command, envp) != 0)
	// {
	// 	free_array(command, -1);
	// 	return ((void)update_status(NOTFOUND));
	// }
	execve(path, command, envp);
	free_array(command, -1);
	return (ERROR);
}
