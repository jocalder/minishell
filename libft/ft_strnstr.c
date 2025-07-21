/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:38:04 by vgoyzuet          #+#    #+#             */
/*   Updated: 2024/12/23 17:44:33 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	blen;
	size_t	llen;

	if (!*little)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	blen = ft_strlen(big);
	llen = ft_strlen(little);
	if (len > blen)
		len = blen;
	while (len >= llen)
	{
		if (ft_strncmp(big, little, llen) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
