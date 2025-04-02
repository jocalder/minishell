/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:52:49 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/02/09 18:16:25 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char *error)
{
	if (!error)
		ft_printf_fd(2, "Error\n");
	else
		ft_printf_fd(2, "Error: %s\n", error);
	exit(EXIT_FAILURE);
}
