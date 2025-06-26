#include "minishell.h"

int	ft_pwd(t_cmd *cmd, char *pwd)
{
	char	*value;
	char	*builtin;
	
	value = NULL;
	builtin = cmd->token->value;
	cmd->token = cmd->token->next;
	while (cmd->token && cmd->token->type != ARG)
		cmd->token = cmd->token->next;
	if (cmd->token && cmd->token->type == ARG)
	{
		value = cmd->token->value;
		if (is_option(value))
		{
			w_builtin_usage(builtin, value);
			return (update_status(SYNTAX));
		}
	}
	if (!pwd)
	{
		write(STDERR_FILENO, "pwd: cannot get the current directory\n", 39);
		return (update_status(ERROR));
	}
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (update_status(OK));
}
