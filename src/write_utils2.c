#include "minishell.h"

void	w_not_such(char *value)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
}

void	w_command_not_found(char *value)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, ": command not found\n", 21);
}

void	w_parse_execution(t_cmd *cmd)
{
	t_cmd	*cur;
	t_token	*head;

	cur = cmd;
	while (cur)
	{
		head = cur->token;
		while (cur->token)
		{
			if (cur->token->type == REDIR_IN || cur->token->type == REDIR_OUT
				|| cur->token->type == HEREDOC || cur->token->type == APPEND)
			{
				if (!cur->token->next || !cur->token->next->value)
				{
					if (cur->next)
						write(STDERR_FILENO, ERROR1, ft_strlen(ERROR1));
				}
			}
			cur->token = cur->token->next;
		}
		cur->token = head;
		cur = cur->next;
	}
}
