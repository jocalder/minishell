/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:34:15 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/06/05 20:30:05 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **arr, int i)
{
	if (!arr || !*arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_exit_free(int EXIT, char *message, char **arr)
{
	free_array(arr, -1);
	if (EXIT == EXIT_FAILURE)
		ft_perror(message);
	else
	{
		ft_printf(message);
		exit(EXIT);
	}
}
