#include "minishell.h"

void	free_prompt(t_prompt **prompt, bool check)
{
	if (!prompt || !*prompt)
		return ;
	if ((*prompt)->value)
		free((*prompt)->value);
	if ((*prompt)->cwd)
		free((*prompt)->cwd);
	if ((*prompt)->user)
		free((*prompt)->user);
	if ((*prompt)->display)
		free((*prompt)->display);
	(*prompt)->value = NULL;
	(*prompt)->user = NULL;
	(*prompt)->cwd = NULL;
	(*prompt)->display = NULL;
	if (check)
	{
		free(*prompt);
		*prompt = NULL;
	}
}

static void	free_token(t_token *token)
{
	t_token	*cur;
	t_token	*next;

	if (!token)
		return ;
	cur = token;
	while (cur)
	{
		next = cur->next;
		if (cur->value)
			free(cur->value);
		cur->value = NULL;
		free(cur);
		cur = next;
	}
}

static void	free_cmd(t_cmd *cmd)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (!cmd)
		return ;
	cur = cmd;
	while (cur)
	{
		next = cur->next;
		if (cur->value)
			free(cur->value);
		if (cur->token)
		{
			free_token(cur->token);
			cur->token = NULL;
		}
		cur->value = NULL;
		free(cur);
		cur = next;
	}
}

void	free_input(t_input **input, bool check)
{
	if (!input || !*input)
		return ;
	(*input)->pipes = 0;
	if ((*input)->value)
		free((*input)->value);
	if ((*input)->cmd)
	{
		free_cmd((*input)->cmd);
		(*input)->cmd = NULL;
	}
	(*input)->value = NULL;
	if (check)
	{
		free(*input);
		*input = NULL;
	}
}

void	free_all(t_mini *data, bool check)
{
	t_cmd	*cur_cmd;
	t_token	*last;
	char	*tmp;

	if (!data)
		return ;
	if (!check && data->input && data->input->cmd)
	{
		cur_cmd = data->input->cmd;
		while (cur_cmd->next)
			cur_cmd = cur_cmd->next;
		last = last_token(cur_cmd->token);
		tmp = ft_strjoin(ft_strdup("_="), last->value);
		if (!tmp)
			exit_free(data, ERROR);
		if (is_existing_var(data->envp, tmp))
			set_existing_var(&data->envp, tmp);
		else
			set_new_var(&data->envp, tmp, count_str(data->envp));
		free(tmp);
	}
	free_envp(data, check);
	free_prompt(&data->prompt, check);
	free_input(&data->input, check);
}
