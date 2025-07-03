#include "minishell.h"

int	ft_env(t_token *token, char **exp_vars)
{
	char	*builtin;

	builtin = token->value;
	token = token->next;
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG)
	{
		if (is_option(token->value))
			w_builtin_usage(builtin, token->value);
		else
			write(STDERR_FILENO, "minishell: env: too many arguments\n", 36);
		return (update_status(SYNTAX));
	}
	while (*exp_vars)
	{
		if (ft_strchr(*exp_vars, '='))
		{
			write(STDOUT_FILENO, *exp_vars, ft_strlen(*exp_vars));
			write(STDOUT_FILENO, "\n", 1);
		}
		exp_vars++;
	}
	return (update_status(OK));
}
