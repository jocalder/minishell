#include "minishell.h"

void	append_token(t_cmd *cmd, t_token **new, int type)
{
	t_token *cur;

	if (!cmd || !new || !*new)
		return ;
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

static t_token	*last_token(t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = token;
	while (last->next)
		last = last->next;
	return (last);
}

int	get_type(t_token *token, char *value)
{
	t_token	*last;

	last = last_token(token);
	if (!last)
		return (CMD);
	else if (last->type == HEREDOC)
		return (ENDOFFILE);
	else if (last->prev
		&& (last->type == APPEND || last->type == REDIR_IN || last->type == REDIR_OUT))
		return (FILE_PATH);
	else if (ft_strncmp(value, "<", ft_strlen(value)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(value, ">", ft_strlen(value)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(value, "<<", ft_strlen(value)) == 0)
		return (HEREDOC);
	else if (ft_strncmp(value, ">>", ft_strlen(value)) == 0)
		return (APPEND);
	else
		return (ARG);
}
