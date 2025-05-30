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

int	is_redir(char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strncmp(str, "<<<", 3) == 0 || ft_strncmp(str, ">>>", 3) == 0
		|| ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0
		|| ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
		return (1);
	return (0);
}
