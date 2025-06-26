#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	bool	suppress_newline;

	suppress_newline = false;
	cmd->token = cmd->token->next;
	while (cmd->token && cmd->token->type != ARG)
		cmd->token = cmd->token->next;
	while (cmd->token && (cmd->token->type == ARG
		&& ft_strncmp(cmd->token->value, "-n", 3) == 0))
	{
		suppress_newline = true;
		cmd->token = cmd->token->next;
	}
	while (cmd->token && cmd->token->type == ARG)
	{
		write(STDOUT_FILENO, cmd->token->value, ft_strlen(cmd->token->value));
		if (cmd->token->next && cmd->token->next->type == ARG)
			write(STDOUT_FILENO, " ", 1);
		cmd->token = cmd->token->next;
	}
	if (!suppress_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (update_status(OK));
}
