/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:34:15 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/03 15:14:25 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **arr, int i)
{
	if (!arr || !*arr)
		return ;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}
