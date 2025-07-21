/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:39 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:40 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_exported_vars(char ***ptr, int size)
{
	char	*tmp;
	bool	swapped;
	int		i;

	if (!ptr || !*ptr || !**ptr || !***ptr)
		return ;
	tmp = NULL;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		i = 0;
		while (i < (size - 1))
		{
			if (ft_strncmp(ptr[0][i], ptr[0][i + 1],
					ft_strlen(ptr[0][i]) + 1) > 0)
			{
				tmp = ptr[0][i];
				ptr[0][i] = ptr[0][i + 1];
				ptr[0][i + 1] = tmp;
				swapped = true;
			}
			i++;
		}
	}
}

static void	print_exported_vars(char **exp_vs)
{
	char	*tmp;

	if (!exp_vs || !*exp_vs || !**exp_vs)
		return ;
	sort_exported_vars(&exp_vs, count_str(exp_vs));
	tmp = NULL;
	while (*exp_vs)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		tmp = ft_strchr(*exp_vs, '=');
		if (tmp)
		{
			write(STDOUT_FILENO, *exp_vs,
				(ft_strlen(*exp_vs) - ft_strlen(++tmp)));
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, tmp, ft_strlen(tmp));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
		{
			write(STDOUT_FILENO, *exp_vs, ft_strlen(*exp_vs));
			write(STDOUT_FILENO, "\n", 1);
		}
		exp_vs++;
	}
}

int	local_case(t_mini *data, t_token *token, char *tmp)
{
	char	*var;

	if (!data || !token)
		return (update_status(ERROR));
	if (!tmp)
	{
		tmp = ft_strdup(token->value);
		if (!tmp)
			return (update_status(ERROR));
		tmp = ft_strjoin(tmp, "=");
		if (!tmp)
			return (update_status(ERROR));
		var = ft_strjoin(tmp, mini_getenv(token->value, data->vars));
	}
	else
		var = ft_strdup(token->value);
	if (!var)
		return (update_status(ERROR));
	if (is_existing_var(data->exp_vs, var))
		set_existing_var(&data->exp_vs, var);
	else
		set_new_var(&data->exp_vs, var, count_str(data->exp_vs));
	unset_var(&data->vars, var, count_str(data->vars));
	return (free(var), OK);
}

int	ft_export(t_mini *data, t_token *token, char *builtin)
{
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG && is_option(token->value))
		return (w_builtin_usage(builtin, token->value), update_status(SYNTAX));
	if (!token)
		return ((print_exported_vars(data->exp_vs)), update_status(OK));
	update_status(OK);
	while (token && token->type == ARG)
	{
		if (!is_validate_id(token->value))
		{
			update_status(ERROR_FD);
			w_invalid_identifier(builtin, token->value);
			token = token->next;
			continue ;
		}
		if (is_existing_var(data->vars, token->value))
			local_case(data, token, ft_strchr(token->value, '='));
		else if (!is_existing_var(data->exp_vs, token->value))
			set_new_var(&data->exp_vs, token->value, count_str(data->exp_vs));
		else
			set_existing_var(&data->exp_vs, token->value);
		token = token->next;
	}
	return (g_status);
}
