#include "minishell.h"

static int	split_input(t_input *input)
{
	char	*str;
	char	*start;
	t_cmd	*cur;
	size_t	len;
	//int		state;
	int		quote;

	if (!input || !input->value)
		return (ERROR);
	str = ft_strdup(input->value);
	if (!str)
		return (ERROR);
	start = str;
	while (*start)
	{
		while (*start && is_spacetab(*start))
			start++;
		if (*start == '|')
		{
			start++;
			if (*start == '|' || !input->cmd)
			{
				if (*(start + 1) == '|')
				{
					if (*(start + 2) != '|')
						write(2, "zsh: parse error near `|'", 25);
					else
						write(2, "zsh: parse error near `||'", 26);
					return (free(str), E_UNSTK);
				}
				return (free(str), ERROR);
			}
			while (*start && is_spacetab(*start))
				start++;
			if (!*start)
				return (free(str), ERROR);
			else if (*start == '|')
			{
				if (*(start + 1) != '|')
					write(2, "zsh: parse error near `|'", 25);
				else
					write(2, "zsh: parse error near `||'", 26);
				return (free(str), E_UNSTK);
			}
			input->pipes++;
			continue ;
		}
		len = 0;
		cur = NULL;
		//state = 0;
		quote = 0;
		while (start[len])
		{
			cur = ft_calloc(1, sizeof(t_cmd));
			if (!cur)
				return (free(str), ERROR);
			while (start[len] && !is_spacetab(start[len]))
				len++;
			while (start[len])
			{
				while (start[len] && is_spacetab(start[len]))
					len++;
				if (is_quote(start[len]))
				{
					quote = start[len];
					while (start[len] && start[len] != quote)
						len++;
					if (!start[len])
						return (free(str), ERROR);
					continue ;
				}
				if (is_redir(start[len]))
				{
					while (start[len] && !is_spacetab(start[len]))
						len++;
					if (!start[len])
						return (free(str), ERROR);
					continue ;
				}
				if (start[len] == '|')
					break ;
			}
			append_cmd(input, cur, ft_substr(start, 0, len));
			/*split_cmd*/
			// state = split_cmd(cur);
			// if (state != OK)
			// 	return (free(str), state);
		}
		start += len;
	}
	return (free(str), OK);
}

int	set_input(t_mini *data)
{
	int	state;

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
	state = split_input(data->input);
	if (state != OK)
		return (state);
	/*invented_input*/ /*choose a number of case (1 ~ 4)*/
	invented_input(data->input);
	printf_input(data->input);
	return (OK);
}
