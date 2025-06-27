#include "minishell.h"

void	w_builtin_usage(char *builtin, char *invalid_opt)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, ": ", 3);
	if (ft_strncmp(invalid_opt, "--", 2) == 0 && ft_strlen(invalid_opt) > 2)
		write(STDERR_FILENO, "--", 2);
	else
	{
		write(STDERR_FILENO, "-", 1);
		invalid_opt++;
		write(STDERR_FILENO, invalid_opt, 1);
	}
	write(STDERR_FILENO, ": invalid option\n", 18);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, ": usage: ", 10);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, "\n", 1);
}

bool	is_option(char *value)
{
	if ((ft_strncmp(value, "--", 2) == 0 && ft_strlen(value) > 2)
		|| (ft_strncmp(value, "-", 1) == 0 && ft_strlen(value) > 1))
		return (true);
	return (false);
}

bool	is_builtin(t_token *token)
{
	char	*value;

	if (!token || !token->value || token->type != CMD)
		return (false);
	value = token->value;
	if (ft_strncmp(value, "echo", 5) == 0
		|| ft_strncmp(value, "pwd", 4) == 0
		|| ft_strncmp(value, "cd", 3) == 0
		|| ft_strncmp(value, "export", 7) == 0
		|| ft_strncmp(value, "unset", 6) == 0
		|| ft_strncmp(value, "env", 4) == 0
		|| ft_strncmp(value, "exit", 5) == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_mini *data, t_cmd *cmd, char **envp)
{
	char	*builtin;

	if (!data || !cmd)
		return (update_status(ERROR));
	(void)envp;
	builtin = cmd->token->value;
	if (ft_strncmp(builtin, "echo", 5) == 0)
		return (update_status(ft_echo(cmd)));
	else if (ft_strncmp(builtin, "pwd", 4) == 0)
		return (update_status(ft_pwd(cmd, data->pwd)));
	else if (ft_strncmp(builtin, "cd", 3) == 0)
			return (update_status(ft_cd(data, cmd)));
	// else if (ft_strncmp(builtin, "env", 4) == 0)
	// 	return (update_status(ft_env(cmd)));
	// else if (ft_strncmp(builtin, "export", 7) == 0)
	// 	return (update_status(ft_export(cmd)));
	// else if (ft_strncmp(builtin, "unset", 6) == 0)
	// 	return (update_status(ft_unset(cmd)));
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (update_status(ft_exit(data, cmd)));
	return (OK);
}
