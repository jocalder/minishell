#include "minishell.h"

bool	has_cmd_type(t_token *token)
{
	if (!token)
		return (false);
	while (token)
	{
		if (token->type == CMD)
			return (true);
		token = token->next;
	}
	return (false);
}

int	set_local_var(t_mini *data, t_token *token)
{
	t_token	*cur;

	if (!data || !token)
		return (update_status(ERROR));
	cur = token;
	while (cur && (cur->type == REDIR_IN || cur->type == REDIR_OUT
		|| cur->type == APPEND || cur->type == HEREDOC
		|| cur->type == ENDOFFILE))
		cur = cur->next;
	if (cur && cur->type != VAR)
		return (OK);
	while (cur && cur->type == VAR)
	{
		if (is_existing_var(data->exp_vs, token->value))
			set_existing_var(&data->exp_vs, token->value);
		if (is_existing_var(data->vars, token->value))
			set_existing_var(&data->vars, token->value);
		else
			set_new_var(&data->vars, token->value, count_str(data->vars));
		cur = cur->next;
	}
	return (update_status(OK));
}
