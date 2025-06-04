#include "minishell.h"

void	append_token(t_cmd *cmd, t_token **new, int type, bool flag)
{
	t_token	*cur;

	if (!cmd || !new || !*new)
		return ;
	(*new)->type = type;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	(*new)->flag = flag;
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

int	get_type(t_token *token, char *value, bool check)
{
	t_token	*last;

	last = last_token(token);
	if (!last && !is_redir(value))
		return (CMD);
	else if (last && last->type == HEREDOC)
		return (ENDOFFILE);
	else if (last && last->prev
		&& (last->type == APPEND || last->type == REDIR_IN
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
