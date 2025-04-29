#include "minishell.h"

static void input_one(t_input *input)
{
	t_cmd	*cur;

	cur = NULL;
	input->value = ft_strdup("cat < input | wc -l");
	if (!input->value)
		return ((void)printf("1.Alloc error\n"));
	input->pipes = 1;
	input->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!input->cmd)
		return ((void)printf("2.Alloc error\n"));
	cur = input->cmd;
	cur->value = ft_strdup("cat < input");
	if (!cur->value)
		return ((void)printf("3.Alloc error\n"));
	cur->token = ft_calloc(1, sizeof(t_token));
	if (!cur->token)
		return ((void)printf("4.Alloc error\n"));
	cur->token->value = ft_strdup("cat");
	if (!cur->token->value)
		return ((void)printf("5.Alloc error\n"));
	cur->token->type = CMD;
	cur->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next)
		return ((void)printf("6.Alloc error\n"));
	cur->token->next->value = ft_strdup("<");
	if (!cur->token->next->value)
		return ((void)printf("7.Alloc error\n"));
	cur->token->next->type = REDIR_IN;
	cur->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next)
		return ((void)printf("8.Alloc error\n"));
	cur->token->next->next->value = ft_strdup("input");
	if (!cur->token->next->next->value)
		return ((void)printf("9.Alloc error\n"));
	cur->token->next->next->type = FILE_PATH;
	cur->token->next->next->next = NULL;
	cur->next = ft_calloc(1, sizeof(t_cmd));
	if (!cur->next)
		return ((void)printf("10.Alloc error\n"));
	cur->next->value = ft_strdup("wc -l");
	if (!cur->next->value)
		return ((void)printf("11.Alloc error\n"));
	cur->next->token = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token)
		return ((void)printf("12.Alloc error\n"));
	cur->next->token->value = ft_strdup("wc");
	if (!cur->next->token->value)
		return ((void)printf("13.Alloc error\n"));
	cur->next->token->type = CMD;
	cur->next->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next)
		return ((void)printf("14.Alloc error\n"));
	cur->next->token->next->value = ft_strdup("-l");
	if (!cur->next->token->next->value)
		return ((void)printf("15.Alloc error\n"));
	cur->next->token->next->type = OPC;
	cur->next->token->next->next = NULL;
	cur->next->next = NULL;
}

static void	input_two(t_input *input)
{
	t_cmd	*cur;

	cur = NULL;
	input->value = ft_strdup("echo \"$USER\" >> output");
	if (!input->value)
		return ((void)printf("Alloc error\n"));
	input->pipes = 0;
	input->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!input->cmd)
		return ((void)printf("Alloc error\n"));
	cur = input->cmd;
	cur->value = ft_strdup("echo \"$USER\" >> output");
	if (!cur->value)
		return ((void)printf("Alloc error\n"));
	cur->token = ft_calloc(1, sizeof(t_token));
	if (!cur->token)
		return ((void)printf("Alloc error\n"));
	cur->token->value = ft_strdup("echo");
	if (!cur->token->value)
		return ((void)printf("Alloc error\n"));
	cur->token->type = CMD;
	cur->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next)
		return ((void)printf("Alloc error\n"));
	cur->token->next->value = ft_strdup("$USER");
	if (!cur->token->next->value)
		return ((void)printf("Alloc error\n"));
	cur->token->next->type = VAR;
	cur->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next)
		return ((void)printf("Alloc error\n"));
	cur->token->next->next->value = ft_strdup(">>");
	if (!cur->token->next->next->value)
		return ((void)printf("Alloc error\n"));
	cur->token->next->next->type = APPEND;
	cur->token->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next->next)
		return ((void)printf("Alloc error\n"));
	cur->token->next->next->next->value = ft_strdup("output");
	if (!cur->token->next->next->next->value)
		return ((void)printf("Alloc error\n"));
	cur->token->next->next->next->type = FILE_PATH;
	cur->token->next->next->next->next = NULL;
	cur->next = NULL;
}

static void	input_three(t_input *input)
{
	input->value = ft_strdup("cat << EOF | grep '\n' ' ' | cat > output");
	if (!input->value)
		return ((void)printf("Alloc error\n"));
	return ;
}

void	invented_input(t_input *input)
{
	int choise;

	if (!input || !input->value)
		return ;
	choise = ft_atoi(input->value);
	if (choise >= 1 && choise <= 3)
	{
		printf("Choise: %d\n", choise);
		free(input->value);
		if (choise == 1)
			input_one(input);
		else if (choise == 2)
			input_two(input);
		else
			input_three(input);
	}
	else
		return ((void)printf("Wrong choice when try invented input\n"));
}

static char	*token_type_str(int type)
{
	if (type == 0)
		return ("CMD");
	else if (type == 1)
		return ("OPC");
	else if (type == 2)
		return ("S_QUOTE");
	else if (type == 3)
		return ("D_QUOTE");
	else if (type == 4)
		return ("REDIR_IN");
	else if (type == 5)
		return ("REDIR_OUT");
	else if (type == 6)
		return ("APPEND");
	else if (type == 7)
		return ("HEREDOC");
	else if (type == 8)
		return ("ENDOFFILE");
	else if (type == 9)
		return ("FILE_PATH");
	else if (type == 10)
		return ("VAR");
	else
		return ("UNKNOWN");
}

void	printf_input(t_input *input)
{
	int		i;
	int		j;
	t_cmd	*cur_cmd;
	t_token	*cur_token;

	if (!input || !input->value)
		return ((void)printf("Input: (null)\n"));
	printf("Input: %s\n", input->value);
	printf("Quantity pipes: %d\n\n", input->pipes);

	if (!input->cmd)
		return ((void)printf("No commands found.\n"));

	i = 0;
	cur_cmd = input->cmd;
	while (cur_cmd)
	{
		printf("┌────────────────────────────────────┐\n");
		printf("│ CMD[%d]: %-25s│\n", i, cur_cmd->value ? cur_cmd->value : "(null)");
		printf("├──────────────┬────────────────────┬────────────\n");
		printf("│ Token Index  │ Value              │ Type       \n");
		printf("├──────────────┼────────────────────┼────────────\n");

		j = 0;
		cur_token = cur_cmd->token;
		while (cur_token)
		{
			printf("│ %-12d │ %-18s │ %-6s \n",
				j,
				cur_token->value ? cur_token->value : "(null)",
				token_type_str(cur_token->type));
			j++;
			cur_token = cur_token->next;
		}
		printf("└──────────────┴────────────────────┴────────────\n\n");

		i++;
		cur_cmd = cur_cmd->next;
	}
}
