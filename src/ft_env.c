#include "minishell.h"

/*Must be in parent process*/
/*Variables are being updated only in the child process*/
int	ft_env(t_token *token, char **envp)
{
	char	*builtin;
	int		i;

	builtin = token->value;
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
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (update_status(OK));
}
