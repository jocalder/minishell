/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:03:56 by vgoyzuet          #+#    #+#             */
/*   Updated: 2024/12/26 00:29:55 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*buffer;

	if (num != 0 && size > SIZE_MAX / num)
		return (NULL);
	buffer = malloc(size * num);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, num * size);
	return (buffer);
}
