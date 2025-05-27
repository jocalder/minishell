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

int	count_token(t_token *token)
{
	int	count;

	count = 0;
	if (!token)
		return (count);
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_token	*last_token(t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = token;
	while (last->next)
		last = last->next;
	return (last);
}

int	update_status(int new_status)
{
	g_status = new_status;
	return (g_status);
}
