#include "minishell.h"

void	printf_input(t_input *input)
{
	int		i;
	int		j;
	t_cmd	*cur_cmd;
	t_token	*cur_token;

	if (!input || !input->value)
		return ((void)printf("nill"));
	printf("Input: %s\n", input->value);
	printf("Quantity pipes: %d\n", input->pipes);
	i = 0;
	if (!input->cmd || !*(input->cmd))
		return ((void)printf("There not CMD\n"));
	cur_cmd = *(input->cmd);
	while (cur_cmd)
	{
		printf("CMD[%d]: %s\n", i, cur_cmd->value);
		if (!cur_cmd->token || !*(cur_cmd->token))
			return ((void)printf("There not more Tokens\n"));
		cur_token = *(cur_cmd->token);
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
