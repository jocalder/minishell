#include "minishell.h"

void	w_openquote(unsigned char quote)
{
	write(STDERR_FILENO, ERROR5, 55);
	write(STDERR_FILENO, &quote, 1);
	write(STDERR_FILENO, "\'\n", 3);
	write(STDERR_FILENO, ERROR6, 50);
}

static void	w_wildcard(int c)
{
	write(STDERR_FILENO, "minishell: wildcard '", 22);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "' is not supported\n", 20);
}

void	w_unexpected(int c)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, "syntax error near unexpected token `", 37);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "'\n", 3);
}

void	w_unsupported(char *str)
{
	int		c;

	if (!str)
		return ;
	c = str[0];
	if (ft_strncmp(str, "&&", 2) == 0)
		write(STDERR_FILENO, ERROR7, 52);
	else if (ft_strncmp(str, "||", 2) == 0)
		write(STDERR_FILENO, ERROR2, 52);
	else if (c == '*' || c == '?')
		w_wildcard(c);
	else if (c == '[' && ((ft_strlen(str) - 1) > 0 && !is_spacetab(str[1])))
		write(STDERR_FILENO, ERROR9, 51);
	else if (c == '\\')
		write(STDERR_FILENO, ERROR10, 34);
	else if (str[ft_strlen(str) - 1] != '(' && str[ft_strlen(str) - 1] != ')')
		w_unexpected(c);
	else
		w_unexpected(str[ft_strlen(str) - 1]);
}
