/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:10:12 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/02 12:56:24 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcl;
	size_t	copyl;

	srcl = ft_strlen(src);
	if (size > 0)
	{
		if (srcl >= size)
			copyl = size - 1;
		else
			copyl = srcl;
		ft_memcpy(dst, src, copyl);
		dst[copyl] = '\0';
	}
	return (srcl);
}
