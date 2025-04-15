/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:22:43 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/04/15 17:11:32 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(t_list **lst, const char *s)
{
	char	*cpy;
	size_t	i;

	if (s == NULL)
		return (NULL);
	cpy = ft_malloc(lst, ft_strlen((char *)s) + 1, sizeof(char *));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
