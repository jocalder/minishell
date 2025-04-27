#include "minishell.h"

void	free_prompt(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->value)
		free(prompt->value);
	if (prompt->cwd)
		free(prompt->cwd);
	if (prompt->display)
		free(prompt->display);
	free(prompt);
}

void	free_input(t_input *input)
{
	if (!input)
		return ;
	/**/
	free(input);
}

void	free_all(t_mini *data)
{
	if (!data)
		return ;
	free_prompt(data->prompt);
	free_input(data->input);
}