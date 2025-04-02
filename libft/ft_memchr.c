/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:15:32 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/02 13:18:30 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n == 0)
		return (NULL);
	while (n--)
	{
		if (*(const unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
