#include "minishell.h"

int	execute_builtin(t_mini *data, t_cmd *cmd)
{
	char	*builtin;

	if (!data || !cmd)
		return (update_status(ERROR));
	builtin = cmd->token->value;
	if (ft_strncmp(builtin, "echo", 5) == 0)
		return (update_status(ft_echo(cmd->token)));
	else if (ft_strncmp(builtin, "pwd", 4) == 0)
		return (update_status(ft_pwd(cmd->token, data->pwd)));
	else if (ft_strncmp(builtin, "cd", 3) == 0)
		return (update_status(ft_cd(data, cmd->token)));
	else if (ft_strncmp(builtin, "env", 4) == 0)
		return (update_status(ft_env(cmd->token, data->exp_vars)));
	else if (ft_strncmp(builtin, "export", 7) == 0)
		return (update_status(ft_export(data, cmd->token->next,
					cmd->token->value)));
	else if (ft_strncmp(builtin, "unset", 6) == 0)
		return (update_status(ft_unset(data, cmd->token)));
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (update_status(ft_exit(data, cmd->token)));
	return (OK);
}
