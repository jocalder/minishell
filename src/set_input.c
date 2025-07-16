#include "minishell.h"

int	split_cmd(t_mini *data, t_cmd **cmd)
{
	t_token	*new;
	char	*start;
	int		type;

	if (!data || !cmd || !*cmd)
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
		if (new_token(data, *cmd, &new, &start) != OK)
			return (free(new->value), free(new), g_status);
		type = get_type(*cmd, (*cmd)->token, new->value, new->flag);
		append_token(*cmd, &new, type);
		if ((new && new->value) && !is_supported(new->value, new->flag))
			return (w_unsupported(new->value), update_status(SYNTAX));
	}
	return (OK);
}

int	split_input(t_mini *data, t_input *input)
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
		if (new)
			if (split_cmd(data, &new) != OK)
				return (g_status);
		start += len;
	}
	printf_input(input);
	return (update_status(OK));
}

int	set_input(t_mini *data)
{
	if (!data || !data->input)
		return (update_status(ERROR));
	free_input(&data->input, false);
	data->input->value = readline(data->prompt->value);
	if (!data->input->value)
	{
		write(STDOUT_FILENO, "exit\n", 6);
		exit_free(data, g_status);
	}
	else if (!*(data->input->value))
		return (OK);
	add_history(data->input->value);
	return (split_input(data, data->input));
}
