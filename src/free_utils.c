#include "minishell.h"

void	free_prompt(t_prompt *prompt, bool check)
{
	if (!prompt)
		return ;
	if (prompt->value)
		free(prompt->value);
	if (prompt->cwd)
		free(prompt->cwd);
	if (prompt->display)
		free(prompt->display);
	prompt->user = NULL;
	if (check)
		free(prompt);
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
		free(cur);
		cur = next;
	}
}

void	free_input(t_input *input, bool check)
{
	if (!input)
		return ;
	input->pipes = 0;
	if (input->value)
		free(input->value);
	if (input->cmd)
	{
		free_cmd(input->cmd);
		input->cmd = NULL;
	}
	if (check)
		free(input);
}

void	free_all(t_mini *data, bool check)
{
	if (!data)
		return ;
	free_prompt(data->prompt, check);
	free_input(data->input, check);
}
