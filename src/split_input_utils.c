#include "minishell.h"

int	validate_pipe(t_input *input, char **str)
{
	while (**str && is_spacetab(**str))
		(*str)++;
	if (**str != '|')
		return (OK);
	input->pipes++;
	if (count_cmd(input->cmd) < input->pipes)
		return ((void)write(STDERR_FILENO, PARSE_ERROR1, 31), update_status(E_UNSTK));
	(*str)++;
	if (**str != '|')
	{
		while (**str && is_spacetab(**str))
			(*str)++;
		if (**str == '\0')
			return (update_status(ERROR));
		if (**str != '|')
			return (OK);
		else if (*(*str + 1) != '|')
			return ((void)write(STDERR_FILENO, PARSE_ERROR1, 31), update_status(E_UNSTK));
		return ((void)write(STDERR_FILENO, PARSE_ERROR2, 32), update_status(E_UNSTK));
	}
	else if (*(*str + 1) == '|' && *(*str + 2) != '|')
		return ((void)write(STDERR_FILENO, PARSE_ERROR1, 31), update_status(E_UNSTK));
	else if (*(*str + 1) == '|' && *(*str + 2) == '|')
		return ((void)write(STDERR_FILENO, PARSE_ERROR2, 32), update_status(E_UNSTK));
	return (update_status(ERROR));
}

t_cmd	*new_cmd(char *start, size_t *len)
{
	unsigned char	quote;
	t_cmd			*new;
	
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	while (start[*len])
	{
		while (start[*len] && is_spacetab(start[*len]))
			(*len)++;
		if (start[*len] && is_quote(start[*len]))
		{
			quote = (unsigned char)start[(*len)++];
			while (start[*len] && start[*len] != quote)
				(*len)++;
			if (!start[*len])
				return (free(new), NULL);
			(*len)++;
			continue ;
		}
		if (start[*len] == '|' || !start[*len])
			break ;
		(*len)++;
	}
	return (new);
}

void	append_cmd(t_input *input, t_cmd *new, char *value)
{
	t_cmd	*cur;

	cur = NULL;
	if (!input->cmd)
	{
		input->cmd = new;
		input->cmd->value = value;
		input->cmd->token = NULL;
		input->cmd->next = NULL;
	}
	else
	{
		cur = input->cmd;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		cur->next->value = value;
		cur->next->token = NULL;
		cur->next->next = NULL;
	}
}

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

char	*expand_content(char *value)
{
	return (value);
	// char	*new_value;
	// char	*tmp;
	// size_t	len;

	// if (!value)
	// 	return (NULL);
	// new_value = ft_strdup("");
	// while (*value)
	// {
	// 	tmp = NULL;
	// 	if (*value == '$')
	// 	{
	// 		value++;
	// 		if (value[len] == '$')
	// 			tmp = ft_itoa((int)getpid());
	// 		else if (value[len] == '?')
	// 			tmp = ft_itoa(g_status);
	// 		else
	// 			tmp = ft_substr(value, 0, len);
	// 	}
	// 	new_value = ft_strjoin(new_value, tmp);
	// }
	// return (free(value), new_value);
}

int	get_type(t_token *token, char *value)
{
	t_token	*last;

	last = last_token(token);
	if (!last)
		return (CMD);
	else if (last->type == HEREDOC)
		return (ENDOFFILE);
	else if (last->prev && (last->type == APPEND || last->type == REDIR_IN || last->type == REDIR_OUT))
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
