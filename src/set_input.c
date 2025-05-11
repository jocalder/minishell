#include "minishell.h"

// static int	split_cmd(t_cmd *cmd)
// {
// 	char	*start;
// 	char	*end;
// 	t_token	*token;

// 	token = NULL;
// 	start = cmd->value;
// 	while (*start)
// 	{
// 		while (*start && is_spacetab(*start))
// 			start++;
// 		//
// 	}
// 	return (OK);
// }

static int	split_input(t_input *input)
{
	char			*start;
	t_cmd			*new;
	size_t			len;

	if (!input || !input->value)
		return (ERROR);
	start = input->value;
	while (*start)
	{
		if (validate_pipe(input, &start) != OK)
			return (g_status);
		reset_var(&new, &len);
		while (start[len] && start[len] != '|')
		{
			if (new_cmd(&new, start, &len) != OK)
				return (g_status);
		}
		// if (split_cmd(new) != OK)
		// 	return (g_status);
		append_cmd(input, new, ft_substr(start, 0, len));
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
	if (data->input->value && *(data->input->value))
		add_history(data->input->value);
	/*new_branch*/
	if (!*(data->input->value))
		return (update_status(OK));
	return (split_input(data->input));
}
