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
	cur->next->token->next->type = ARG;
	cur->next->token->next->next = NULL;
	cur->next->next = NULL;
}

static void	input_two(t_input *input)
{
	t_cmd	*cur;

	cur = NULL;
	input->value = ft_strdup("echo var_expanded >> output");
	if (!input->value)
		return ((void)printf("1.Alloc error\n"));
	input->pipes = 0;
	input->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!input->cmd)
		return ((void)printf("2.Alloc error\n"));
	cur = input->cmd;
	cur->value = ft_strdup("echo var_expanded >> output");
	if (!cur->value)
		return ((void)printf("3.Alloc error\n"));
	cur->token = ft_calloc(1, sizeof(t_token));
	if (!cur->token)
		return ((void)printf("4.Alloc error\n"));
	cur->token->value = ft_strdup("echo");
	if (!cur->token->value)
		return ((void)printf("5.Alloc error\n"));
	cur->token->type = BUILTIN;
	cur->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next)
		return ((void)printf("6.Alloc error\n"));
	cur->token->next->value = ft_strdup("var_expanded");
	if (!cur->token->next->value)
		return ((void)printf("7.Alloc error\n"));
	cur->token->next->type = ARG;
	cur->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next)
		return ((void)printf("8.Alloc error\n"));
	cur->token->next->next->value = ft_strdup(">>");
	if (!cur->token->next->next->value)
		return ((void)printf("9.Alloc error\n"));
	cur->token->next->next->type = APPEND;
	cur->token->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next->next)
		return ((void)printf("10.Alloc error\n"));
	cur->token->next->next->next->value = ft_strdup("output");
	if (!cur->token->next->next->next->value)
		return ((void)printf("11.Alloc error\n"));
	cur->token->next->next->next->type = FILE_PATH;
	cur->token->next->next->next->next = NULL;
	cur->next = NULL;
}

static void	input_three(t_input *input)
{
	t_cmd	*cur;

	cur = NULL;
	input->value = ft_strdup("cat << EOF | grep a | cat > output");
	if (!input->value)
		return ((void)printf("1.Alloc error\n"));
	input->pipes = 2;
	input->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!input->cmd)
		return ((void)printf("2.Alloc error\n"));
	cur = input->cmd;
	cur->value = ft_strdup("cat << EOF");
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
	cur->token->next->value = ft_strdup("<<");
	if (!cur->token->next->value)
		return ((void)printf("7.Alloc error\n"));
	cur->token->next->type = HEREDOC;
	cur->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next)
		return ((void)printf("8.Alloc error\n"));
	cur->token->next->next->value = ft_strdup("EOF");
	if (!cur->token->next->next->value)
		return ((void)printf("9.Alloc error\n"));
	cur->token->next->next->type = ENDOFFILE;
	cur->token->next->next->next = NULL;
	cur->next = ft_calloc(1, sizeof(t_cmd));
	if (!cur->next)
		return ((void)printf("10.Alloc error\n"));
	cur->next->value = ft_strdup("grep a");
	if (!cur->next->value)
		return ((void)printf("11.Alloc error\n"));
	cur->next->token = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token)
		return ((void)printf("12.Alloc error\n"));
	cur->next->token->value = ft_strdup("grep");
	if (!cur->next->token->value)
		return ((void)printf("13.Alloc error\n"));
	cur->next->token->type = CMD;
	cur->next->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next)
		return ((void)printf("14.Alloc error\n"));
	cur->next->token->next->value = ft_strdup("a");
	if (!cur->next->token->next->value)
		return ((void)printf("15.Alloc error\n"));
	cur->next->token->next->type = ARG;
	cur->next->token->next->next = NULL;
	cur->next->next = ft_calloc(1, sizeof(t_cmd));
	if (!cur->next->next)
		return ((void)printf("16.Alloc error\n"));
	cur->next->next->value = ft_strdup("cat > output");
	if (!cur->next->next->value)
		return ((void)printf("17.Alloc error\n"));
	cur->next->next->token = ft_calloc(1, sizeof(t_token));
	if (!cur->next->next->token)
		return ((void)printf("18.Alloc error\n"));
	cur->next->next->token->value = ft_strdup("cat");
	if (!cur->next->next->token->value)
		return ((void)printf("19.Alloc error\n"));
	cur->next->next->token->type = CMD;
	cur->next->next->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->next->token->next)
		return ((void)printf("20.Alloc error\n"));
	cur->next->next->token->next->value = ft_strdup(">");
	if (!cur->next->next->token->next->value)
		return ((void)printf("21.Alloc error\n"));
	cur->next->next->token->next->type = REDIR_OUT;
	cur->next->next->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->next->token->next->next)
		return ((void)printf("22.Alloc error\n"));
	cur->next->next->token->next->next->value = ft_strdup("output");
	if (!cur->next->next->token->next->next->value)
		return ((void)printf("23.Alloc error\n"));
	cur->next->next->token->next->next->type = FILE_PATH;
	cur->next->next->token->next->next->next = NULL;
	cur->next->next->next = NULL;
}

static void	input_four(t_input *input)
{
	t_cmd	*cur;

	cur = NULL;
	input->value = ft_strdup("cat < infile1 < infile2 | wc -l > outfile1 >> outfile2");
	if (!input->value)
		return((void)printf("Alloc error\n"));
	input->pipes = 1;
	input->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!input->cmd)
		return((void)printf("Alloc error\n"));
	cur = input->cmd;
	cur->value = ft_strdup("cat < infile1 < infile2");
	if (!cur->value)
		return((void)printf("Alloc error\n"));
	cur->token = ft_calloc(1, sizeof(t_token));
	if (!cur->token)
		return((void)printf("Alloc error\n"));
	cur->token->value = ft_strdup("cat");
	if (!cur->token->value)
		return((void)printf("Alloc error\n"));
	cur->token->type = CMD;
	cur->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next)
		return((void)printf("Alloc error\n"));
	cur->token->next->value = ft_strdup("<");
	if (!cur->token->next->value)
		return((void)printf("Alloc error\n"));
	cur->token->next->type = REDIR_IN;
	cur->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next)
		return((void)printf("Alloc error\n"));
	cur->token->next->next->value = ft_strdup("infile1");
	if (!cur->token->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->token->next->next->type = FILE_PATH;
	cur->token->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next->next)
		return((void)printf("Alloc error\n"));
	cur->token->next->next->next->value = ft_strdup("<");
	if (!cur->token->next->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->token->next->next->next->type = REDIR_IN;
	cur->token->next->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->token->next->next->next->next)
		return((void)printf("Alloc error\n"));
	cur->token->next->next->next->next->value = ft_strdup("infile2");
	if (!cur->token->next->next->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->token->next->next->next->next->type = FILE_PATH;
	cur->token->next->next->next->next->next = NULL;
	cur->next = ft_calloc(1, sizeof(t_cmd));
	if (!cur->next)
		return((void)printf("Alloc error\n"));
	cur->next->value = ft_strdup("wc -l > outfile1 >> outfile2");
	if (!cur->next->value)
		return((void)printf("Alloc error\n"));
	cur->next->token = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token)
		return((void)printf("Alloc error\n"));
	cur->next->token->value = ft_strdup("wc");
	if (!cur->next->token->value)
		return((void)printf("Alloc error\n"));
	cur->next->token->type = CMD;
	cur->next->token->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->value = ft_strdup("-l");
	if (!cur->next->token->next->value)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->type = ARG;
	cur->next->token->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next->next)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->value = ft_strdup(">");
	if (!cur->next->token->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->type = REDIR_OUT;
	cur->next->token->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next->next->next)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->next->value = ft_strdup("outfile1");
	if (!cur->next->token->next->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->next->type = FILE_PATH;
	cur->next->token->next->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next->next->next->next)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->next->next->value = ft_strdup(">>");
	if (!cur->next->token->next->next->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->next->next->type = APPEND;
	cur->next->token->next->next->next->next->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next->token->next->next->next->next->next)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->next->next->next->value = ft_strdup("outfile2");
	if (!cur->next->token->next->next->next->next->next->value)
		return((void)printf("Alloc error\n"));
	cur->next->token->next->next->next->next->next->type = FILE_PATH;
	cur->next->token->next->next->next->next->next->next = NULL;
	cur->next->next = NULL;
}

void	invented_input(t_input *input)
{
	int choise;

	if (!input || !input->value)
		return ;
	choise = ft_atoi(input->value);
	if (choise >= 1 && choise <= 4)
	{
		printf("Choise: %d\n", choise);
		free(input->value);
		if (choise == 1)
			input_one(input);
		else if (choise == 2)
			input_two(input);
		else if (choise == 3)
			input_three(input);
		else
			input_four(input);
	}
	else
		return ((void)printf("Wrong choice when try invented input\n"));
}

static char	*token_type_str(int type)
{
	if (type == 0)
		return ("CMD");
	else if (type == BUILTIN)
		return ("BUILTIN");
	else if (type == ARG)
		return ("ARG");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == ENDOFFILE)
		return ("ENDOFFILE");
	else if (type == FILE_PATH)
		return ("FILE_PATH");
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
		printf("┌────────────────────────────────────\n");
		printf("│ CMD[%d]: %-25s\n", i, cur_cmd->value ? cur_cmd->value : "(null)");
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
