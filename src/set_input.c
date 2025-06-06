#include "minishell.h"

int	split_cmd(t_cmd **cmd)
{
	t_token	*new;
	char	*start;
	int		type;

	if (!cmd || !*cmd)
		return (update_status(ERROR));
	start = (*cmd)->value;
	while (*start)
	{
		while (*start && is_spacetab(*start))
			start++;
		new = NULL;
		new = ft_calloc(1, sizeof(t_token));
		if (!new)
			return (update_status(ERROR));
		new->value = ft_strdup("");
		new->flag = false;
		if (new_token(*cmd, &new, &start) != OK)
			return (g_status);
		type = get_type((*cmd)->token, new->value, new->flag);
		append_token(*cmd, &new, type);
		// This comprobation is in the execution,
		// because the syntax error is post to check the access of the command
		if (!is_supported(new->value))
			return (w_unsupported(new->value), update_status(SINTAX));
	}
	return (OK);
}

int	split_input(t_input *input)
{
	char			*start;
	t_cmd			*new;
	size_t			len;

	if (!input || !input->value)
		return (update_status(ERROR));
	start = input->value;
	while (*start)
	{
		if (validate_pipe(input, &start) != OK)
			return (g_status);
		new = NULL;
		len = 0;
		while (start[len] && start[len] != '|')
		{
			if (new_cmd(&new, start, &len) != OK)
				return (g_status);
		}
		append_cmd(input, &new, ft_substr(start, 0, len));
		if (split_cmd(&new) != OK)
			return (g_status);
		start += len;
	}
	return (OK);
}

int	set_input(t_mini *data)
{
	if (!data)
		return (update_status(ERROR));
	data->input->value = readline(data->prompt->value);
	if (!data->input->value)
		return (update_status(END));
	else if (!*(data->input->value))
		return (OK);
	add_history(data->input->value);
	return (split_input(data->input));
}
