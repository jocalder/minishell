#include "minishell.h"

int	new_token(t_mini *data, t_cmd *cmd, t_token **new, char **start)
{
	char			*tmp;
	size_t			len;

	if (!new || !start || !*start)
		return (update_status(ERROR));
	while (**start && !is_spacetab(**start))
	{
		len = 0;
		tmp = NULL;
		if (is_redir(*start) && ft_strncmp((*new)->value, "", 1) != 0)
			break ;
		if (is_quote(*start[len]))
			(*new)->flag = true;
		tmp = check_cases(data, cmd, start, &len);
		if (!tmp)
			return (g_status);
		(*new)->value = ft_strjoin((*new)->value, tmp);
		if (!(*new)->value)
			return (free(tmp), update_status(ERROR));
		*start += len;
		free(tmp);
	}
	return (OK);
}

t_token	*last_token(t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = token;
	while (last->next)
		last = last->next;
	return (last);
}

int	get_type(t_cmd *cmd, t_token *token, char *value, bool check)
{
	t_token	*last;

	last = last_token(token);
	if (cmd && (is_validate_id(value) && ft_strchr(value, '='))
		&& (!has_type(token, CMD) && !has_type(token, REDIR_IN)
			&& !has_type(token, HEREDOC) && !has_type(token, REDIR_OUT)
			&& !has_type(token, APPEND)))
		return (VAR);
	else if ((!last || (last && last->type == VAR)) && !is_redir(value))
		return (CMD);
	else if (last && last->type == HEREDOC)
		return (ENDOFFILE);
	else if (last && (last->type == APPEND || last->type == REDIR_IN
			|| last->type == REDIR_OUT))
		return (FILE_PATH);
	else if (ft_strncmp(value, "<", ft_strlen(value)) == 0 && !check)
		return (REDIR_IN);
	else if (ft_strncmp(value, ">", ft_strlen(value)) == 0 && !check)
		return (REDIR_OUT);
	else if (ft_strncmp(value, "<<", ft_strlen(value)) == 0 && !check)
		return (HEREDOC);
	else if (ft_strncmp(value, ">>", ft_strlen(value)) == 0 && !check)
		return (APPEND);
	else
		return (ARG);
}

void	append_token(t_cmd *cmd, t_token **new, int type)
{
	t_token	*cur;

	if (!cmd || !new || !*new || !(*new)->value)
		return ;
	if (ft_strncmp((*new)->value, "", ft_strlen((*new)->value)) == 0
		&& type != ENDOFFILE)
	{
		free((*new)->value);
		free(*new);
		*new = NULL;
		return ;
	}
	(*new)->type = type;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	if (!cmd->token)
		cmd->token = *new;
	else
	{
		cur = cmd->token;
		while (cur->next)
			cur = cur->next;
		cur->next = *new;
		(*new)->prev = cur;
	}
}
