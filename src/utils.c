#include "minishell.h"

int	is_spacetab(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	count_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (count);
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
