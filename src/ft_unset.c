#include "minishell.h"

static void	update_envp(t_mini *data)
{
	free_array(data->envp, -1);
	data->envp = envpdup(data->exp_vs);
	if (!data->envp)
		update_status(ERROR);
}

int	ft_unset(t_mini *data, t_token *token)
{
	char	*builtin;

	builtin = token->value;
	token = token->next;
	if (token && token->type == ARG && is_option(token->value))
		return (w_builtin_usage(builtin, token->value), update_status(SYNTAX));
	update_status(OK);
	while (token && token->type == ARG)
	{
		if (!is_validate_id(token->value) || ft_strchr(token->value, '='))
		{
			update_status(ERROR_FD);
			w_invalid_identifier(builtin, token->value);
			token = token->next;
			continue ;
		}
		if (is_existing_var(data->exp_vs, token->value))
			unset_var(&data->exp_vs, token->value,
				count_str(data->exp_vs));
		if (is_existing_var(data->vars, token->value))
			unset_var(&data->vars, token->value, count_str(data->vars));
		update_envp(data);
		token = token->next;
	}
	return (g_status);
}
