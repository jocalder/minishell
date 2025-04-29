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

static void	free_token(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	tmp = NULL;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = tmp;
	}
	free(token);
}

static void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return ;
	tmp = NULL;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->value);
		free_token((*cmd)->token);
		free(*cmd);
		*cmd = tmp;
	}
	free(cmd);
}

void	free_input(t_input *input, bool check)
{
	if (!input)
		return ;
	if (input->value)
		free(input->value);
	if (input->cmd)
		free_cmd(input->cmd);
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
