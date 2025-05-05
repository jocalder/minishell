#include "minishell.h"

// bool	redir_error(char *input)
// {
// 	while (*input)
// 	{
// 		if (*input == '<' || *input == '>')
// 		{
// 			input++;
// 			while (*input && is_spacetab(*input))
// 				input++;
// 			if (!*input|| *input == '|')
// 				return (true);
			
// 		}
// 		input++;
// 	}
// 	return (false);
// }

// int	check_input(char *input)
// {
// 	if (has_opened_quote(input)
// 		|| has_opened_pipe(input)
// 		|| has_inspected_char(input)
// 		|| has_logic_ops(input)
// 		|| has_wildcard(input)
// 		|| redir_error(input))
// 		return (ERROR);
// 	return (OK);
// }

void	append_cmd(t_input *input, t_cmd *new, char *value)
{
	t_cmd	*cur;

	cur = NULL;	
	if (!input->cmd)
	{
		input->cmd = new;
		input->cmd->value = value;
		input->cmd->token = NULL;
		input->cmd->next = NULL;
	}
	else
	{
		cur = input->cmd;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		cur->next->value = value;
		cur->next->token = NULL;
		cur->next->next = NULL;
	}
}
