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

bool	is_special(char *str)
{
	size_t	len;

	if (!str || !*str)
		return (false);
	len = 0;
	if (str[len] == '$'
		&& (str[len + 1] && !is_spacetab(str[len + 1])))
		return (true);
	return (false);
}

bool	is_supported(char *str)
{
	int		c;
	size_t	i;

	if (!str || !*str)
		return (false);
	c = str[0];
	i = ft_strlen(str) - 1;
	if ((ft_strncmp(str, "&&", 2) == 0) || (ft_strncmp(str, "||", 2) == 0)
		|| c == ';' || c == '&' || c == '\\' || c == '`'
		|| c == '(' || c == ')' || str[i] == '(' || str[i] == ')'
		|| c == '*' || c == '?'
		|| (c == '[' && (str[1] && !is_spacetab(str[1]))))
		return (false);
	return (true);
}
