#include "minishell.h"

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

bool	is_option(char *value)
{
	if ((ft_strncmp(value, "--", 2) == 0 && ft_strlen(value) > 2)
		|| (ft_strncmp(value, "-", 1) == 0 && ft_strlen(value) > 1))
		return (true);
	return (false);
}

bool	is_validate_id(char *id)
{
	int	i;

	if (!id || !*id)
		return (update_status(ERROR_FD), false);
	i = 0;
	if (!ft_isalpha(id[i]) && id[i] != '_')
		return (update_status(ERROR_FD), false);
	i = 1;
	while (id[i] && id[i] != '=')
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (update_status(ERROR_FD), false);
		i++;
	}
	return (true);
}

bool	is_new_var(char **envp, char *var)
{
	char	*tmp;
	size_t	len;

	tmp = ft_strchr(var)
	while (*envp)
	{
		//
		envp++;
	}
	return (true);
}
