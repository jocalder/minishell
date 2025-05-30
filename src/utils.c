#include "minishell.h"

bool	is_spacetab(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

bool	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	is_redir(char *str)
{
	if (!str || !*str)
		return (false);
	if (ft_strncmp(str, "<<<", 3) == 0 || ft_strncmp(str, ">>>", 3) == 0
		|| ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0
		|| ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
		return (true);
	return (false);
}

bool	is_builtin(char *value)
{
	if (!value)
		return (false);
	if (ft_strncmp(value, "echo", 5) == 0
		|| ft_strncmp(value, "cd", 3) == 0
		|| ft_strncmp(value, "pwd", 4) == 0
		|| ft_strncmp(value, "export", 7) == 0
		|| ft_strncmp(value, "unset", 6) == 0
		|| ft_strncmp(value, "env", 4) == 0
		|| ft_strncmp(value, "exit", 5) == 0)
		return (true);
	return (false);
}
