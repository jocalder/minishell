#include "minishell.h"

void	printf_input(t_input *input)
{
	int		i;
	int		j;
	t_cmd	*cur_cmd;
	t_token	*cur_token;

	if (!input || !input->value)
		printf("nill");
	printf("Input: %s\n", input->value);
	printf("Quantity pipes: %d", input->pipes);
	i = 0;
	cur_cmd = (*input).cmd;
	while (cur_cmd)
	{
		printf("CMD[%d]: %s\n", i, cur_cmd->value);
		cur_token = (*cur_cmd).token;
		j = 0;
		while (cur_token)
		{
			printf("Token[%d]\n", j);
			printf("Type: %d\n", cur_token->type);
			printf("Value: %s\n", cur_token->value);
			j++;
			cur_token = cur_token->next;
		}
		i++;
		cur_cmd = cur_cmd->next;
	}
}
