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

bool	is_supported(char **str, size_t len)
{
	char	*start;
	size_t	end;
	char	c;

	if (!str || !*str)
		return (true);
	start = *str + len;
	c = start[0];
	end = ft_strlen(start) - 1;
	while (end > 0 && is_spacetab((start)[end]))
		end--;
	if ((ft_strncmp(start, "&&", 2) == 0) || (ft_strncmp(start, "||", 2) == 0)
		|| c == ';' || c == '&' || c == '\\' || c == '`'
		|| c == '(' || c == ')' || start[end] == '(' || start[end] == ')'
		|| c == '*' || c == '?'
		|| unvalidate_bracket(start))
	{
		*str = start;
		return (false);
	}
	return (true);
}
