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

int	new_cmd(t_cmd **new, char *start, size_t *len)
{
	unsigned char	quote;
	
	*new = ft_calloc(1, sizeof(t_cmd));
	if (!*new)
		return (update_status(ERROR));
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
				return (update_status(ERROR));
			(*len)++;
			continue ;
		}
		if (start[*len] == '|' || !start[*len])
			break ;
		(*len)++;
	}
	return (OK);
}

void	append_cmd(t_input *input, t_cmd **new, char *value)
{
	t_cmd	*cur;

	cur = NULL;
	if (!input->cmd)
	{
		input->cmd = *new;
		input->cmd->value = value;
		input->cmd->token = NULL;
		input->cmd->next = NULL;
	}
	else
	{
		cur = input->cmd;
		while (cur->next)
			cur = cur->next;
		cur->next = *new;
		cur->next->value = value;
		cur->next->token = NULL;
		cur->next->next = NULL;
	}
}

void	append_token(t_cmd *cmd, t_token *new, char *value, int type)
{
	t_token	*cur;

	cur = NULL;
	if (!cmd->token)
	{
		cmd->token = new;
		cmd->token->value = value;
		cmd->token->type = type;
		cmd->token->next = NULL;
	}
	else
	{
		cur = cmd->token;
		while(cur.next)
			cur = cur.next;
		cur->next = new;
		cur->next->value = value;
		cur->next->type = type;
		cur->next->next = NULL;
	}
}

char	*expand_content(char *value)
{
	char	*new_value;
	char	*tmp;
	size_t	len;

	if (!value)
		return (NULL);
	new_value = ft_strdup("");
	while (*value)
	{
		tmp = NULL;
		if (*value == '$')
		{
			if (start[len] == '$')
					tmp = ft_itoa((int)getpid());
			//
		}
		new_value = ft_strjoin(new_value, tmp);
	}
	return (new_value);
}
