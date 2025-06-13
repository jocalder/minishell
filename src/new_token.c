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
		return ((void)update_status(SYNTAX), NULL);
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
		return (w_openquote(quote), update_status(SYNTAX));
	return (OK);
}

char	*quote_case(t_cmd *cmd, char *start, size_t *len)
{
	unsigned char	quote;
	char			*tmp;

	if (!start)
		return ((void)update_status(ERROR), NULL);
	quote = (unsigned char)start[(*len)++];
	if (close_quote(start, quote, len) != OK)
		return (NULL);
	tmp = ft_substr(start, 1, (*len) - 1);
	if (!tmp)
		return ((void)update_status(ERROR), NULL);
	if (quote == '\"')
		tmp = expand_content(tmp, last_token(cmd->token));
	(*len)++;
	return (tmp);
}

char	*special_case(t_cmd *cmd, char *start, size_t *len)
{
	char	*tmp;

	(*len)++;
	while (start[*len]
		&& (!is_spacetab(start[*len]) && !is_quote(start[*len])))
		(*len)++;
	tmp = expand_content(ft_substr(start, 0, *len), last_token(cmd->token));
	return (tmp);
}

char	*check_cases(t_cmd *cmd, t_token *new, char **start, size_t *len)
{
	char	*tmp;

	if (!cmd || !new || !start || !*start)
		return ((void)update_status(ERROR), NULL);
	tmp = NULL;
	if (is_quote(*start[*len]))
	{
		new->flag = true;
		tmp = quote_case(cmd, *start, len);
	}
	else if (is_special(*start))
		tmp = special_case(cmd, *start, len);
	else if (is_redir(*start))
		tmp = get_redir(start, len);
	else
	{
		tmp = ft_substr(*start, 0, ++(*len));
		if (!tmp)
			return ((void)update_status(ERROR), NULL);
	}
	return (tmp);
}
