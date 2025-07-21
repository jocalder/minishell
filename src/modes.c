/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:53 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/21 12:20:39 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interactive_mode(t_mini *data)
{
	while (1)
	{
		wait_signal(0);
		if (set_prompt(data->prompt, data->exp_vs) != OK)
			check_exit_status(g_status, data);
		if (set_input(data) == OK)
		{
			if (handler_execution(data, data->input->cmd, data->envp) != OK)
				check_exit_status(g_status, data);
		}
		else
			check_exit_status(g_status, data);
		free_all(data, false);
	}
}

static void	command_mode_one(t_mini *data)
{
	char	*line;

	free_prompt(&data->prompt, true);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		exit_free(data, ERROR);
	data->input->value = ft_strdup("");
	if (!data->input->value)
	{
		free(line);
		exit_free(data, ERROR);
	}
	while (line)
	{
		data->input->value = ft_strjoin(data->input->value, line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (ft_strncmp(data->input->value, "\n",
			ft_strlen(data->input->value)) == 0
		|| !*data->input->value)
		exit_free(data, OK);
	if (split_input(data, data->input) == OK)
		handler_execution(data, data->input->cmd, data->envp);
	exit_free(data, g_status);
}

static void	command_mode_two(t_mini *data, char *arg)
{
	free_prompt(&data->prompt, true);
	data->input->value = ft_strdup(arg);
	if (!data->input->value)
		exit_free(data, ERROR);
	if (split_input(data, data->input) == OK)
		handler_execution(data, data->input->cmd, data->envp);
	exit_free(data, g_status);
}

void	command_mode(t_mini *data, char **argv, int argc)
{
	if (argc == 1)
		command_mode_one(data);
	else if (argc > 2 && ft_strncmp(argv[1], "-c", 3) == 0)
		command_mode_two(data, argv[2]);
	else
	{
		free_all(data, true);
		write(STDERR_FILENO, USAGE, 29);
		update_status(SYNTAX);
	}
}
