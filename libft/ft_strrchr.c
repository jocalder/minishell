/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:17:22 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/02 13:03:18 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;
	const char	*ptr;

	len = ft_strlen(s);
	ptr = s + len;
	while (ptr != s)
	{
		ptr--;
		if (*ptr == (unsigned char)c)
		{
			return ((char *)ptr);
		}
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)(s + len));
	}
	return (NULL);
}
