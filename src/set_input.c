#include "minishell.h"

//Reduce lines
//Consider the cases when redir and next argument are joined (DONE)
//Consider add flag in cases quote for redir and EOF in Heredoc (DONE)
int	split_cmd(t_cmd **cmd)
{
	t_token			*new;
	char			*tmp;
	size_t			len;
	unsigned char	quote;
	char			*start;

	start = (*cmd)->value;
	if (!cmd || !*cmd || !start)
		return (update_status(ERROR));
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
		while (*start && !is_spacetab(*start))
		{
			len = 0;
			tmp = NULL;
			if (is_quote(start[len]))
			{
				new->flag = true;
				quote = (unsigned char)start[len++];
				while (start[len] && start[len] != quote)
					len++;
				if (!start[len])
					return (update_status(ERROR));
				tmp = ft_substr(start, 1, len - 1);
				if (quote == '\"')
					tmp = expand_content(tmp, ((last_token((*cmd)->token))->type));
				len++;
			}
			else if (start[len] == '$' && (start[len + 1] && !is_spacetab(start[len + 1])))
			{
				len++;
				while (start[len] && (!is_spacetab(start[len]) && !is_quote(start[len])))
					len++;
				tmp = expand_content(ft_substr(start, 0, len),  ((last_token((*cmd)->token))->type));
			}
			else if (is_redir(start))
			{
				tmp = get_redir(&start, &len);
				if (!tmp)
					return (free(new->value), free(new), g_status);
			}
			else
				tmp = ft_substr(start, 0, ++len);
			new->value = ft_strjoin(new->value, tmp);
			if (!new->value)
				return (free(tmp), update_status(ERROR));
			start += len;
			free(tmp);
		}
		if (ft_strncmp(new->value, "", ft_strlen(new->value)) != 0)
			append_token(*cmd, &new, get_type((*cmd)->token, new->value, new->flag), new->flag);
		else
		{
			free(new->value);
			free(new);
		}
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
			new = new_cmd(start, &len);
			if (!new)
				return (update_status(ERROR));
		}
		append_cmd(input, new, ft_substr(start, 0, len));
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
	if (data->input->value && *(data->input->value))
		add_history(data->input->value);
	if (!*(data->input->value))
		return (OK);
	return ((split_input(data->input)));
}
