/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:13:06 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/02 12:59:49 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	to_copy;
	size_t	i;

	dlen = 0;
	slen = 0;
	i = 0;
	while (dst[dlen] != '\0' && dlen < size)
		dlen++;
	while (src[slen] != '\0')
		slen++;
	if (size <= dlen)
		return (size + slen);
	to_copy = size - dlen -1;
	if (to_copy > slen)
		to_copy = slen;
	while (i < to_copy)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + to_copy] = '\0';
	return (dlen + slen);
}
