/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:52:57 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/04/15 17:41:39 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clean(t_list	**lst)
{
	t_list	*cur;
	t_list	*next;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}

void	ft_free(t_list **lst, void *buffer)
{
	t_list	*cur;
	t_list	*prev;

	if (!lst || !*lst || !buffer)
		return ;
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		if (cur->content == buffer)
		{
			if (prev)
				prev->next = cur->next;
			else
			{
				*lst = cur->next;
				lst = &(*lst);
			}
			if (buffer)
				free(buffer);
			return (free(cur));
		}
		prev = cur;
		cur = cur->next;
	}
}

void	*ft_malloc(t_list **lst, size_t num, size_t size)
{
	void	*buffer;
	t_list	*node;

	buffer = ft_calloc(num, size);
	if (!buffer)
		return (NULL);
	node = ft_lstnew(buffer);
	if (!node)
	{
		free(buffer);
		return (NULL);
	}
	ft_lstadd_back(lst, node);
	return (buffer);
}

/*
int main(void)
{
    t_list	*alloc = NULL;
	t_list	*head = NULL;
	char	*str1 = NULL;
	char	*str2 = NULL;
	int		*arr = NULL;
	t_list	*node = NULL;

	str1 = ft_malloc(&alloc, 10, sizeof(char));
	str2 = ft_malloc(&alloc, 9, sizeof(char));
	arr = ft_malloc(&alloc, 8, sizeof(int));
	node = ft_malloc(&alloc, 1, sizeof(t_list));
	if (!str1 || !str2 || !arr || !node)
	{
		printf("Error: Alloc");
		return (-1);
	}
	printf("Buffers allocates:\n");
	printf("str1:	%p\n", str1);
	printf("str2:	%p\n", str2);
	printf("arr:	%p\n", arr);
	printf("node:	%p\n", node);
	printf("\nList allocates:\n");
	head = alloc;
	while (alloc)
	{
		printf("buffer: %p\n", alloc->content);
		alloc = alloc->next;
	}
	alloc = head;
	ft_free(&alloc, node);
	head = alloc;
	printf("\nList after ft_free\n");
	while (alloc)
	{
		printf("buffer:	%p\n", alloc->content);
		alloc = alloc->next;
	}
	alloc = head;
	ft_clean(&alloc);
	printf("\nList after ft_clean\n");
	if (alloc)
	{
		while (alloc)
		{
			printf("buffer:	%p\n", alloc->content);
			alloc = alloc->next;
		}
	}
	else
		printf("List empty\n");
}
*/
