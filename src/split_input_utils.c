#include "minishell.h"

void	reset_var(t_cmd **new, size_t *len)
{
	*new = NULL;
	*len = 0;
}

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

// static void	append_token(t_cmd *cmd, t_token *new, char *value, int type)
// {
// 	t_token	*cur;

// 	cur = NULL;
// 	if (!cmd->token)
// 	{
// 		cmd->token = new;
// 		cmd->token->value = value;
// 		cmd->token->type = type;
// 		cmd->token->next = NULL;
// 	}
// 	else
// 	{
// 		cur = cmd->token;
// 		while(cur.next)
// 			cur = cur.next;
// 		cur->next = new;
// 		cur->next->value = value;
// 		cur->next->type = type;
// 		cur->next->next = NULL;
// 	}
// }

// static void	expand_cmd(char **value)
// {
// 	if (!value)
// 		return ;
	//
// }

// int	split_cmd(t_cmd **cmd, char *start)
// {
// 	t_token	*new;
// 	char	*value;
// 	int		type;
// 	size_t	len;

// 	while (*start)
// 	{
// 		new = NULL;
// 		new = ft_calloc(1, sizeof(t_token));
// 		if (!new)
// 			return (update_status(ERROR));
// 		while (*start && is_spacetab(*start))
// 			start++;
// 		len = 0;
// 		value = NULL;
// 		type = ARG;
// 		if (count_token((*cmd)->token) == 0 && *start)
// 		{
// 			while (start[len] && !is_spacetab(start[len]))
// 				len++;
// 			value = ft_substr(start, 0, len);
// 			expand_cmd(&value);
// 			if (!is_builtin(value))
// 			{
// 				if (access(value, X_OK) == ERROR)
// 					return (write(STDERR_FILENO, CMD_NO_FOUND, 17), update_status(E_USAGE));
// 				type = CMD;
// 			}
// 			else
// 				type = BUILTIN;
// 		}
// 		append_token(*cmd, new, value, type);
// 		start += len;
// 	}
// 	return (OK);
// }
