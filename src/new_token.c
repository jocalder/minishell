#include "minishell.h"

char	*get_redir(char **str, size_t *len)
{
	char	*redir;

	redir = NULL;
	if (ft_strncmp(str[0], "<<<", 3) == 0)
		return ((void)update_status(ERROR), NULL);
	else if (ft_strncmp(str[0], ">>>", 3) == 0)
	{
		write(STDERR_FILENO, ERROR3, 50);
		return ((void)update_status(SINTAX), NULL);
	}
	else if (ft_strncmp(str[0], "<<", 2) == 0
		|| ft_strncmp(str[0], ">>", 2) == 0)
	{
		redir = ft_substr(str[0], 0, 2);
		str[0][++(*len)] = ' ';
	}
	else if (ft_strncmp(str[0], "<", 1) == 0 || ft_strncmp(str[0], ">", 1) == 0)
	{
		redir = ft_substr(str[0], 0, 1);
		str[0][0] = ' ';
	}
	if (redir)
		return (redir);
	else
		return ((void)update_status(ERROR), NULL);
}

static int	close_quote(char *start, unsigned char quote, size_t *len)
{
	if (!start)
		return (update_status(ERROR));
	while (start[*len] && start[*len] != quote)
		(*len)++;
	if (!start[*len])
		return (w_openquote(quote), update_status(SINTAX));
	return (OK);
}

int	quote_case(t_cmd *cmd, char *start, char **tmp, size_t *len)
{
	unsigned char	quote;

	if (!start || !tmp)
		return (update_status(ERROR));
	quote = (unsigned char)start[(*len)++];
	if (close_quote(start, quote, len) != OK)
		return (g_status);
	*tmp = ft_substr(start, 1, (*len) - 1);
	if (quote == '\"')
		*tmp = expand_content(*tmp, last_token(cmd->token));
	(*len)++;
	return (OK);
}

void	special_case(t_cmd *cmd, char *start, char **tmp, size_t *len)
{
	(*len)++;
	while (start[*len]
		&& (!is_spacetab(start[*len]) && !is_quote(start[*len])))
		(*len)++;
	*tmp = expand_content(ft_substr(start, 0, *len), last_token(cmd->token));
}

int	check_cases(t_cmd *cmd, char **start, char **tmp, size_t *len)
{
	if (!cmd || !start || !*start || !tmp)
		return (update_status(ERROR));
	if (is_quote(*start[*len]))
	{
		if (quote_case(cmd, *start, tmp, len) != OK)
			return (g_status);
	}
	else if (is_special(*start))
		special_case(cmd, *start, tmp, len);
	else
	{
		*tmp = get_redir(start, len);
		if (!*tmp)
			return (g_status);
	}
	return (OK);
}
