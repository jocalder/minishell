#include "minishell.h"

static bool	redir_error(char *input)
{
	char	*tmp;

	tmp = input;
	while (*tmp)
	{
		if (*tmp == '<' || *tmp == '>')
		{
			tmp++;
			while (*tmp && is_spacetab(*tmp))
				tmp++;
			if (!*tmp || *tmp == '|')
				return (true);
			
		}
		tmp++;
	}
	return (false);
}

int	check_errors(char *input)
{
	if (has_opened_quote(input)
		|| has_opened_pipe(input)
		|| has_inspected_char(input)
		|| has_logic_ops(input)
		|| has_wildcard(input)
		|| redir_error(input))
		return (ERROR);
	return (OK);
}
