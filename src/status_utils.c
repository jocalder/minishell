/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:16:01 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:16:02 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(t_mini *data, int status)
{
	if (status == ERROR || status == ERROR_FD)
		g_status = 1;
	free_all(data, true);
	rl_clear_history();
	exit(g_status);
}

int	update_status(int new_status)
{
	g_status = new_status;
	return (g_status);
}

void	check_exit_status(int status, t_mini *data)
{
	if (status == ERROR_FD)
		g_status = 1;
	else if (status == ERROR)
	{
		g_status = 1;
		free_all(data, true);
		rl_clear_history();
		exit (g_status);
	}
}
