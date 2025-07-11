#include "minishell.h"

static int	vardup(char ***tmp, char **ptr, int *i, int *j)
{
	(*tmp)[*j] = ft_strdup(ptr[*i]);
	if (!(*tmp)[*j])
	{
		free_array(*tmp, -1);
		while (ptr[*i])
			free((ptr[(*i)++]));
		return (ERROR);
	}
	(*j)++;
	return (OK);
}

int	unset_var(char ***ptr, char *var, int len)
{
	int		i;
	int		j;
	char	**tmp;

	if (!ptr || !*ptr || !var)
		return (update_status(ERROR));
	tmp = ft_calloc(len, sizeof(char *));
	if (!tmp)
		return (update_status(ERROR));
	i = 0;
	j = 0;
	while ((*ptr)[i])
	{
		if (!is_same_var((*ptr)[i], var))
			if (vardup(&tmp, *ptr, &i, &j) != OK)
				return (update_status(ERROR));
		free((*ptr)[i]);
		i++;
	}
	tmp[j] = NULL;
	free(*ptr);
	*ptr = tmp;
	return (OK);
}

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
		if (!is_existing_var(data->vars, token->value))
			set_new_var(&data->vars, token->value, count_str(data->vars));
		else if (is_existing_var(data->exp_vs, token->value))
		{
			unset_var(&data->vars, token->value, count_str(data->vars));
			set_existing_var(&data->exp_vs, token->value);
		}
		else
			set_existing_var(&data->vars, token->value);
		cur = cur->next;
	}
	return (update_status(OK));
}
