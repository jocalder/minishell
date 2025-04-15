/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:45:27 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/04/15 17:25:02 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s = s + wordlen(s, c);
		}
		else
			s++;
	}
	return (count);
}

static	void	*free_strs(t_list **lst, char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		ft_free(lst, strs[i++]);
	ft_free(lst, strs);
	return (NULL);
}

char	**ft_split(t_list **lst, char const *s, char c)
{
	char	**strs;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	strs = ft_malloc(lst, count + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	strs[count] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_substr(lst, s, 0, wordlen(s, c));
			if (!strs[i++])
				return (free_strs(strs));
			s += wordlen(s, c);
		}
		else
			s++;
	}
	return (strs);
}
