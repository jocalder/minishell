/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:33 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/21 12:42:33 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt(t_prompt **prompt, bool check)
{
	if (!prompt || !*prompt)
		return ;
	if ((*prompt)->value)
		free((*prompt)->value);
	if ((*prompt)->cwd)
		free((*prompt)->cwd);
	if ((*prompt)->user)
		free((*prompt)->user);
	if ((*prompt)->display)
		free((*prompt)->display);
	(*prompt)->value = NULL;
	(*prompt)->user = NULL;
	(*prompt)->cwd = NULL;
	(*prompt)->display = NULL;
	if (check)
	{
		free(*prompt);
		*prompt = NULL;
	}
}

static void	free_token(t_token *token)
{
	t_token	*cur;
	t_token	*next;

	if (!token)
		return ;
	cur = token;
	while (cur)
	{
		next = cur->next;
		if (cur->value)
			free(cur->value);
		cur->value = NULL;
		if (cur->line)
			free(cur->line);
		cur->line = NULL;
		if (cur->pipe_hd[0] != -1)
			close(cur->pipe_hd[0]);
		cur->pipe_hd[0] = -1;
		if (cur->pipe_hd[1] != -1)
			close(cur->pipe_hd[1]);
		cur->pipe_hd[1] = -1;
		free(cur);
		cur = next;
	}
}

static void	free_cmd(t_cmd *cmd)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (!cmd)
		return ;
	cur = cmd;
	while (cur)
	{
		next = cur->next;
		if (cur->value)
			free(cur->value);
		if (cur->token)
		{
			free_token(cur->token);
			cur->token = NULL;
		}
		cur->value = NULL;
		free(cur);
		cur = next;
	}
}

void	free_input(t_input **input, bool check)
{
	if (!input || !*input)
		return ;
	(*input)->pipes = 0;
	if ((*input)->value)
		free((*input)->value);
	if ((*input)->cmd)
	{
		free_cmd((*input)->cmd);
		(*input)->cmd = NULL;
	}
	(*input)->value = NULL;
	if (check)
	{
		free(*input);
		*input = NULL;
	}
}

void	free_all(t_mini *data, bool check)
{
	if (!data)
		return ;
	free_envp(data, check);
	free_prompt(&data->prompt, check);
	free_input(&data->input, check);
}
