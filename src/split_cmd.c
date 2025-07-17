#include "minishell.h"

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

static int	get_redir_type(char *value)
{
	if (ft_strncmp(value, "<", ft_strlen(value)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(value, ">", ft_strlen(value)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(value, "<<", ft_strlen(value)) == 0)
		return (HEREDOC);
	else if (ft_strncmp(value, ">>", ft_strlen(value)) == 0)
		return (APPEND);
	return (ARG);
}

static bool	ok(char *value, bool check)
{
	if (!check && (!*value || *value == ' '))
		return (false);
	return (true);
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
	else if (last && last->type == HEREDOC && !is_redir(value)
		&& ok(value, check))
		return (ENDOFFILE);
	else if (last && (last->type == APPEND || last->type == REDIR_IN
			|| last->type == REDIR_OUT) && !is_redir(value) && ok(value, check))
		return (FILE_PATH);
	else if (last && is_redir(last->value))
		return (ARG);
	else if ((ft_strncmp(value, "<", ft_strlen(value)) == 0 && !check)
		|| (ft_strncmp(value, ">", ft_strlen(value)) == 0 && !check)
		|| (ft_strncmp(value, "<<", ft_strlen(value)) == 0 && !check)
		|| (ft_strncmp(value, ">>", ft_strlen(value)) == 0 && !check))
		return (get_redir_type(value));
	else
		return (ARG);
}

void	append_token(t_cmd *cmd, t_token **new, int type)
{
	t_token	*cur;

	if (!cmd || !new || !*new || !(*new)->value)
		return ;
	if (ft_strncmp((*new)->value, "", ft_strlen((*new)->value)) == 0
		&& (type != ENDOFFILE && type != CMD && type != FILE_PATH))
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
