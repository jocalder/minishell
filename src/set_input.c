#include "minishell.h"

static int	is_open_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (1)
	return (0);
}

static int	is_close_quote(int quote, int c)
{
	if (c != quote)
		return (0)
	return (1);
}

static void	count_pipes(char *input, int *pipes)
{
	char	quote;

	if (!input)
		return ;
	while (*input)
	{
		if (is_open_quote(*input))
		{
			quote = *input;
			input++;
			while (*input && !is_close_quote(quote, *input))
				input++;
			continue ;
		}
		if (**input == '|')
		{
			*input++;
			if (**input == '|' || !**input)
				return (-2);
			*pipes++;
			continue ;
		}
		if (**input == '\\' || **input == ';')
			return (-3);
		*input++;
	}
}

static void	set_cmd(t_cmd **cmd, int count)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = NULL;
	if (count)
	{
		cur = ft_calloc(1, sizeof(t_cmd));
		if (!cur)
			return (NULL);
		cur->cmd = NULL;
		cur->arr = NULL;
		cur->type = NULL;
		cur->next = NULL;
		count--;
	}
	next = NULL;
	while (cur && count)
	{
		next = ft_calloc(1, sizeof(t_cmd));
		if (!next)
			return (NULL);
		next->cmd = NULL;
		next->arr = NULL;
		next->type = NULL;
		next->next = NULL;
		cur->next = next;
		cur = cur->next;
		next = NULL;
		count--;
	}
	return (cmd);
}

static t_cmd	**split_input(t_mini *data)
{
	t_cmd	**cmd;
	char	*tmp;
	char	*start;
	int		quote;
	size_t	len;

	if (!data->input->input || !*data->input->input)
		return (NULL);
	cmd = NULL;
	cmd = ft_calloc(data->input->pipes + 2, sizeof(t_cmd *));
	if (!cmd)
		perror (FAIL_ALLOC);
	cmd[data->input->pipes + 1] = NULL;
	tmp = data->input->input;
	if (!set_cmd(cmd, data->input->pipes + 1))
		perror(FAIL_ALLOC);
	if (data->input->pipes == 0)
	{
		(*cmd)->cmd = ft_strdup(data->input->input);
		if (!(*cmd)->cmd)
			perror(FAIL_ALLOC);
		return (cmd);
	}
	while (*tmp && *cmd)
	{
		start = tmp;
		if (is_open_quote(*tmp))
		{
			if (*tmp == '\'')
				(*cmd)->arr->s_quote = true;
			else
				(*cmd)->arr->d_quote = true;
			quote = *tmp;
			tmp++;
			while (*tmp && !is_close_quote(quote, *tmp))
				tmp++;
			if (*tmp)
				(*cmd)->arr->check_close = true;
		}
		if (*tmp == '|')
		{
			start[ft_strlen(tmp)] = NULL;
			*tmp++;
			if (*tmp == '|')
				return (NULL);
			(*cmd)->cmd = ft_substr(start, 0, ft_strlen(start) + 1);
			if (!(*cmd)->cmd)
				return (NULL);
		}
		*cmd = (*cmd)->next;
	}
	return (cmd);
}

void	set_input(t_mini *data, char *prompt)
{
	if (!data || !prompt)	
		return ;
	data->input->input = readline(prompt);
	free(prompt);
	if (!data->input->input)
		return (1);
	if (data->input->input)
		add_history(data->input->input);
	count_pipes(data->input->input, &(data->input->pipes)); //INT MAX -> Alloc error
	if (data->input->pipes == -1)
		perror(OPEN_QUOTE);
	if (data->input->pipes == -2)
		perror(OPEN_PIPE);
	if (data->input->pipes == -3)
		perror(NO_VALID);
	data->input->cmd = split_input(data);
	if (!data->input->cmd)
		perror(FAIL_ALLOC);
	//
}
