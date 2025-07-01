#include "minishell.h"

static void	print_exported_vars(char **envp)
{
	if (!envp || !*envp || !**envp)
		return ;
	while (*envp)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, *envp, ft_strlen(*envp));
		write(STDOUT_FILENO, "\"\n", 2);
		envp++;
	}
}

int	ft_export(t_mini *data, t_token *token)
{
	char	*builtin;

	builtin = token->value;
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG && is_option(token->value))
		return (w_builtin_usage(builtin, token->value), update_status(SYNTAX));
	// else if (!token)
	return ((print_exported_vars(data->cpy_envp)), OK);
	// while (token && token->type = ARG)
	// {
		
	// }
}
