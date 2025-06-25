#include "minishell.h"

static void	w_pwd_usage(char *invalid_opt)
{
	int	c;

	while (invalid_opt && ft_strncmp(invalid_opt, "-", 1) == 0)
		invalid_opt++;
	c = *invalid_opt;
	write(STDERR_FILENO, "minishell: pwd: -", 18);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, ": invalid option\npwd: usage: pwd\n", 34);
}

static bool	is_invalid(char *option)
{
	if (ft_strncmp(option++, "-", 1) == 0)
	{
		if (!option)
			return (false);
		return (true);
	}
	return (false);
}

int	ft_pwd(t_cmd *cmd, char *pwd)
{
	char	*option;
	
	option = NULL;
	cmd->token = cmd->token->next;
	if (cmd->token && cmd->token->type == ARG)
	{
		option = cmd->token->value;
		if (is_invalid(option))
		{
			w_pwd_usage(option);
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
