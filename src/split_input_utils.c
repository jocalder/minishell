#include "minishell.h"

// bool	redir_error(char *input)
// {
// 	while (*input)
// 	{
// 		if (*input == '<' || *input == '>')
// 		{
// 			input++;
// 			while (*input && is_spacetab(*input))
// 				input++;
// 			if (!*input|| *input == '|')
// 				return (true);
			
// 		}
// 		input++;
// 	}
// 	return (false);
// }

// int	check_input(char *input)
// {
// 	if (has_opened_quote(input)
// 		|| has_opened_pipe(input)
// 		|| has_inspected_char(input)
// 		|| has_logic_ops(input)
// 		|| has_wildcard(input)
// 		|| redir_error(input))
// 		return (ERROR);
// 	return (OK);
// }

void	reset_var(t_cmd **new, size_t *len, unsigned char *quote)
{
	*new = NULL;
	*len = 0;
	*quote = 0;
}

int	validate_pipe(t_input *input, char **str)
{
	while (**str && is_spacetab(**str))
		(*str)++;
	if (**str != '|')
		return (OK);
	input->pipes++;
	if (count_cmd(input->cmd) < input->pipes)
		return ((void)write(STDERR_FILENO, PARSE_ERROR1, 31), E_UNSTK);
	(*str)++;
	if (**str != '|')
	{
		while (**str && is_spacetab(**str))
			(*str)++;
		if (**str == '\0')
			return (ERROR);
		if (**str != '|')
			return (OK);
		else if (*(*str + 1) != '|')
			return ((void)write(STDERR_FILENO, PARSE_ERROR1, 31), E_UNSTK);
		return ((void)write(STDERR_FILENO, PARSE_ERROR2, 32), E_UNSTK);
	}
	else if (*(*str + 1) == '|' && *(*str + 2) != '|')
		return ((void)write(STDERR_FILENO, PARSE_ERROR1, 31), E_UNSTK);
	else if (*(*str + 1) == '|' && *(*str + 2) == '|')
		return ((void)write(STDERR_FILENO, PARSE_ERROR2, 32), E_UNSTK);
	return (ERROR);
}

int	new_cmd(t_cmd **new, char *start, size_t *len, unsigned char *quote)
{
	*new = ft_calloc(1, sizeof(t_cmd));
	if (!*new)
	{
		g_status = ERROR;
		return (g_status);
	}
	while (start[*len] && start[*len] != '|')
	{
		printf("hi%zu\n", *len);
		while (start[*len] && is_spacetab(start[*len]))
			(*len)++;
		if (start[*len] && is_quote(start[*len]))
		{
			*quote = (unsigned char)start[*len];
			while (start[*len] && start[*len] != *quote)
				(*len)++;
			if (!start[*len])
			{
				g_status = ERROR;
				return (g_status);
			}
			(*len)++;
		}
		else
			(*len)++;
		printf("bye\n");
	}
	return (OK);
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
