#include "minishell.h"

int	is_spacetab(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*get_special_var(int c)
{
	if (c == '$')
		return (ft_itoa((int)getpid()));
	else if (c == '?')
		return (ft_itoa(g_status));
	return (NULL);
}

char	*get_env_var(char *var)
{
	char	*env;

	if (!var)
		return (ft_strdup(""));
	env = ft_strdup(getenv(var));
	if (!env)
		env = ft_strdup("");
	return (free(var), env);
}
