#include "minishell.h"

static int	count_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (count);
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	validate_pipe(t_input *input, char **str)
{
	while (**str && is_spacetab(**str))
		(*str)++;
	if (**str && **str != '|')
		return (OK);
	input->pipes++;
	if (count_cmd(input->cmd) < input->pipes)
		return ((void)write(STDERR_FILENO, ERROR1, 51), update_status(SINTAX));
	(*str)++;
	if (**str != '|')
	{
		while (**str && is_spacetab(**str))
			(*str)++;
		if (**str == '\0')
			return ((void)write(2, ERROR6, 50), update_status(SINTAX));
		else if (**str != '|')
			return (OK);
		else if (*(*str + 1) != '|')
			return ((void)write(2, ERROR1, 51), update_status(SINTAX));
		return ((void)write(STDERR_FILENO, ERROR2, 52), update_status(SINTAX));
	}
	else if (*(*str + 1) == '|' && *(*str + 2) != '|')
		return ((void)write(STDERR_FILENO, ERROR1, 51), update_status(SINTAX));
	else
		return ((void)write(STDERR_FILENO, ERROR2, 52), update_status(SINTAX));
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
			if (!start[(*len)++])
				return (free(*new), w_openquote(quote), update_status(SINTAX));
			continue ;
		}
		if (start[*len] == '|' || !start[*len])
			break ;
		else if (start[*len] && !is_supported(&start, *len))
			return (free(*new), w_unsupported(start), update_status(SINTAX));
		(*len)++;
	}
	return (OK);
}

void	append_cmd(t_input *input, t_cmd **new, char *value)
{
	t_cmd	*cur;

	if (!input || !*new)
		return ;
	(*new)->value = value;
	(*new)->token = NULL;
	(*new)->next = NULL;
	if (!input->cmd)
		input->cmd = *new;
	else
	{
		cur = input->cmd;
		while (cur->next)
			cur = cur->next;
		cur->next = *new;
	}
}
