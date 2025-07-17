/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:16:04 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:16:05 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	has_type(t_token *token, t_token_type type)
{
	if (!token || type < 0 || type > 8)
		return (false);
	while (token)
	{
		if (token->type == type)
			return (true);
		token = token->next;
	}
	return (false);
}

bool	set_local_var(t_mini *data, t_cmd **cmd, t_token *token)
{
	t_token	*cur;

	cur = token;
	if (cur && cur->type != VAR)
		return (false);
	while (cur && cur->type == VAR && !has_type(cur, CMD))
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
	update_status(OK);
	if (cur)
		return (false);
	*cmd = (*cmd)->next;
	return (true);
}
