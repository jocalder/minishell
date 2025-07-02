/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:51:04 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/02 23:51:07 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc(char **array, int size)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), (size + 1));
	if (new == NULL)
		return (free_array(array, -1), ft_perror("malloc"), NULL);
	while (array && array[i] != NULL && array[i][0] != '\0')
	{
		new[i] = ft_strdup(array[i]);
		if (new[i] == NULL)
			return (free_array(array, -1), ft_perror("malloc"), NULL);
		i++;
	}
	new[i] = NULL;
	i = 0;
	free_array(array, -1);
	return (new);
}
