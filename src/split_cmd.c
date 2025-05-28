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

static char	*handle_expand(char *value, size_t *len)
{
	char	*new_value;

	if (!value)
		return ft_strdup("");
	if (value[*len] == '$' || value[*len] == '?')
		new_value = get_special_var(value[(*len)++]);
	else
	{
		while (value[*len] && value[*len] != '$')
			(*len)++;
		new_value = get_env_var(ft_substr(value, 0, *len));
	}
	return (new_value);
}

char	*expand_content(char *value)
{
	char	*new_value;
	char	*start;
	char	*tmp;
	size_t	len;

	if (!value)
		return (ft_strdup(""));
	new_value = ft_strdup("");
	start = value;
	while (*start)
	{
		tmp = NULL;
		len = 0;
		if (*start == '$' && (start[len + 1] && !is_spacetab(start[len + 1])))
			tmp = handle_expand(++start, &len);
		else
			tmp = ft_substr(start, 0, ++len);
		start += len;
		new_value = ft_strjoin(new_value, tmp);
		free(tmp);
	}
	return (free(value), new_value);
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
