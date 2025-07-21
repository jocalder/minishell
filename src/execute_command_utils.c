/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:25 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/18 16:59:44 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		while (cmd->token->value[i])
			write(STDERR_FILENO, &cmd->token->value[i++], 1);
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
	if (!envp[i])
		return (w_not_such(cmd->token->value), update_status(SUCH), NULL);
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
	return (free_array(directories, i - 1), NULL);
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
	args = ft_calloc(count + 1, sizeof(char *));
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
	int		fd;

	fd = 3;
	while (cmd->token && cmd->token->type != CMD)
		cmd->token = cmd->token->next;
	command = build_full_command(cmd->token);
	path = find_command_path(command[0], envp, cmd);
	if (!path || !*cmd->token->value)
	{
		if (g_status == SUCH)
			return (free_array(command, -1), update_status(ERROR_FD));
		w_command_not_found(*command);
		return (free_array(command, -1), NOTFOUND);
	}
	while (fd < 1024)
		close(fd++);
	if (execve(path, command, envp) != 0)
		return (free_array(command, -1), ERROR_FD);
	return (OK);
}
