/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:52 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:53 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	init_data(&data, envp);
	if (isatty(STDIN_FILENO) && argc == 1)
		interactive_mode(&data);
	else
		command_mode(&data, argv, argc);
	exit (g_status);
}
