#include "minishell.h"

static int	split_input(t_input *input)
{
	char			*start;
	t_cmd			*new;
	size_t			len;
	unsigned char	quote;

	if (!input || !input->value)
		return (ERROR);
	start = input->value;
	while (*start)
	{
		if (validate_pipe(input, &start) != OK)
			return (g_status);
		reset_var(&new, &len, &quote);
		while (start[len] && start[len] != '|')
		{
			if (new_cmd(&new, start, &len, &quote) != OK)
				return (g_status);
			len++;
		}
		append_cmd(input, new, ft_substr(start, 0, len));
		// if (split_cmd(new) != OK)
		// 	return (g_status);
		start += len;
	}
	return (OK);
}

int	set_input(t_mini *data)
{
	if (!data)	
		return (ERROR);
	data->input->value = readline(data->prompt->value);
	if (!data->input->value)
		return (END);
	if (data->input->value && *(data->input->value))
		add_history(data->input->value);
	/*new_branch*/
	if (!*(data->input->value))
		return (OK);
	return (split_input(data->input));
}
