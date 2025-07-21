/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:55:23 by vgoyzuet          #+#    #+#             */
/*   Updated: 2024/12/23 17:43:24 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, n);
	else
	{
		src += n;
		dst += n;
		while (n--)
			*(unsigned char *)(--dst) = *(const unsigned char *)(--src);
	}
	return (dst);
}
