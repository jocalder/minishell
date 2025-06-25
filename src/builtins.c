#include "minishell.h"

// static void	ft_cd(t_mini *data)
// {
// 	char	*home;

// 	home = NULL;
// 	if (!data->args[1])
// 	{
// 		home = getenv("HOME");
// 		if (!home)
// 			perror("minishell: cd: HOME not set\n");
// 		if (chdir(home) != 0)
// 			perror("error home");//change for a similar error message
// 	}
// 	else
// 	{
// 		if (chdir(data->args[1]) != 0)
// 			perror("error route");//change for a similar error message
// 	}
// }

// static void	ft_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	if (!envp)
// 		return ;
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// }

bool	is_builtin(t_token *token)
{
	char	*value;

	if (!token || !token->value || token->type != CMD)
		return (false);
	value = token->value;
	if (ft_strncmp(value, "echo", 5) == 0
		|| ft_strncmp(value, "cd", 3) == 0
		|| ft_strncmp(value, "pwd", 4) == 0
		|| ft_strncmp(value, "export", 7) == 0
		|| ft_strncmp(value, "unset", 6) == 0
		|| ft_strncmp(value, "env", 4) == 0
		|| ft_strncmp(value, "exit", 5) == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_mini *data, t_cmd *cmd)
{
	char	*builtin;

	if (!data || !cmd)
		return (update_status(ERROR));
	builtin = cmd->token->value;
	if (ft_strncmp(builtin, "echo" 5) == 0)
		return (update_status(ft_echo(cmd->next)));
	else if (ft_strncmp(builtin, "pwd", 4) == 0)
		return (update_status(ft_pwd(data, cmd->next)));
	// else if (ft_strncmp(builtin, "env", 4) == 0)
	// 	return (update_status(ft_env(cmd)));
	// else if (ft_strncmp(builtin, "cd", 3) == 0)
	// 	return (update_status(ft_cd(data)));
	// else if (ft_strncmp(builtin, "export", 7) == 0)
	// 	return (update_status(ft_export(cmd)));
	// else if (ft_strncmp(builtin, "unset", 6) == 0)
	// 	return (update_status(ft_unset(cmd)));
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (update_status(ft_exit(cmd)));
}
