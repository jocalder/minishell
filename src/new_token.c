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
		return ((void)write(STDERR_FILENO, ERROR5, 59),
				(void)write(STDERR_FILENO, ERROR6, 50),
				update_status(SINTAX));
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

// int	split_cmd(t_cmd **cmd, char *start)
// {
// 	t_token			*new;
// 	char			*tmp;
// 	size_t			len;
// 	unsigned char	quote;

// 	if (!cmd || !*cmd || !start)
// 		return (update_status(ERROR));
// 	while (*start)
// 	{
// 		while (*start && is_spacetab(*start))
// 			start++;
// 		new = NULL;
// 		new = ft_calloc(1, sizeof(t_token));
// 		if (!new)
// 			return (update_status(ERROR));
// 		new->value = ft_strdup("");
// 		new->flag = false;
// 		while (*start && !is_spacetab(*start))
// 		{
// 			len = 0;
// 			tmp = NULL;
// 			if (start[len] && is_quote(start[len]))
// 			{
// 				new->flag = true;
// 				quote = (unsigned char)start[len++];
// 				if (close_quote(start, quote, &len) != OK)
// 					return (g_status);
// 				tmp = ft_substr(start, 1, len - 1);
// 				if (quote == '\"')
// 					tmp = expand_content(tmp, last_token((*cmd)->token));
// 				len++;
// 			}
// 			else if (start[len] == '$' && (start[len + 1] && !is_spacetab(start[len + 1])))
// 			{
// 				len++;
// 				while (start[len] && (!is_spacetab(start[len]) && !is_quote(start[len])))
// 					len++;
// 				tmp = expand_content(ft_substr(start, 0, len), last_token((*cmd)->token));
// 			}
// 			else if (is_redir(start))
// 			{
// 				tmp = get_redir(&start, &len);
// 				if (!tmp)
// 					return (free(new->value), free(new), g_status);
// 			}
// 			else
// 				tmp = ft_substr(start, 0, ++len);
// 			new->value = ft_strjoin(new->value, tmp);
// 			if (!new->value)
// 				return (free(tmp), update_status(ERROR));
// 			start += len;
// 			free(tmp);
// 		}
// 		append_token(*cmd, &new, get_type((*cmd)->token, new->value, new->flag), new->flag);
// 	}
// 	return (OK);
// }