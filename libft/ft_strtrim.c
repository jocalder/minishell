/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:41:46 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/02 13:11:20 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int		i;
	size_t				len;

	i = 0;
	len = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, s1[i]))
		i++;
	while (len > i && ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, i, len - i));
}
