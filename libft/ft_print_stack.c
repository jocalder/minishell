/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 03:16:41 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/02/06 21:31:53 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_stack(t_list *stack, char *str)
{
	t_list	*current;

	ft_printf("%s\n", str);
	if (!stack)
	{
		ft_printf("empty\n");
		return ;
	}
	current = stack;
	while (current)
	{
		ft_printf("%d\n", *(int *)current->content);
		current = current->next;
	}
}
