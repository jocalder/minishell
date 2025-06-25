#include "minishell.h"

static bool	is_invalided(char *option)
{
	if (ft_strncmp(option++, "-", 1) == 0)
	{
		if (!option)
			return (false);
		return (true);
	}
	return (false);
}

int	ft_pwd(t_mini *data, t_cmd *cmd)
{
	char	*option;

	option = NULL;
	if (cmd->token && cmd->token->type == ARG)
	{
		option = cmd->token->value;
		if (is_invalided(option))
		{
			//
		}
	}
}