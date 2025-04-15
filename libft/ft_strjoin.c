/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:11:00 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/04/15 17:22:20 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(t_list **lst, char const *s1, char const *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	s = ft_malloc(((lst, ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1),
			sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (ft_free(lst, (char *)s1), s);
}
