#include "minishell.h"

static bool	has_redirection(t_cmd *cmd);
{
	if (!cmd)
		return (false);
	while (cmd->token)
	{
		if (token->type == REDIR_IN
			|| token->type == REDIR_OUT
			|| token->type == APPEND
			|| token->type == HEREDOC)
			return (true);
		cmd->token == cmd->token->next;
	}
	return (false);
}

bool	is_single_builtin(t_cmd *cmd)
{
	if (!cmd || cmd->next)
		return (false);
	if (has_redirection(cmd))
		return (false);
	return (is_builtin(cmd->token->value));
}

bool	only_parent(const char *builtin)
{
	if (!builtin)
		return (false);
	if (ft_strncmp(builtin, "cd", 3) == 0
		|| ft_strncmp(builtin, "export", 7) == 0
		|| ft_strncmp(builtin, "unset", 6) == 0
		|| ft_strncmp(builtin, "exit", 5) == 0)
		return (true);
	return (false);
}
