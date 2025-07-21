/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:52:49 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/06/27 05:53:23 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char *error)
{
	if (!error)
		ft_printf_fd(STDERR_FILENO, "Error\n");
	else
		ft_printf_fd(STDERR_FILENO, "Error: %s\n", error);
	exit(EXIT_FAILURE);
}
