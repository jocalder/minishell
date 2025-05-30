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
	if (**str != '|')
		return (OK);
	input->pipes++;
	if (count_cmd(input->cmd) < input->pipes)
		return ((void)write(STDERR_FILENO, ERROR1, 50), update_status(E_UNSTK));
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
			return ((void)write(STDERR_FILENO, ERROR1, 50), update_status(2));
		return ((void)write(STDERR_FILENO, ERROR2, 51), update_status(E_UNSTK));
	}
	else if (*(*str + 1) == '|' && *(*str + 2) != '|')
		return ((void)write(STDERR_FILENO, ERROR1, 50), update_status(E_UNSTK));
	else if (*(*str + 1) == '|' && *(*str + 2) == '|')
		return ((void)write(STDERR_FILENO, ERROR2, 51), update_status(E_UNSTK));
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

	if (!input || !new)
		return ;
	new->value = value;
	new->token = NULL;
	new->next = NULL;
	if (!input->cmd)
		input->cmd = new;
	else
	{
		cur = input->cmd;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
