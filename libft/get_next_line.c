/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:43:33 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/04/15 20:55:07 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*update_line(t_list **lst, char *pre_line)
{
	char	*next_line;
	char	*tmp;

	tmp = ft_strchr(pre_line, '\n');
	next_line = ft_substr(lst, tmp, 1, ft_strlen(tmp));
	if (next_line && !*next_line)
		return (ft_free(lst, pre_line), ft_free(lst, next_line), NULL);
	return (ft_free(lst, pre_line), next_line);
}

static char	*clean_line(t_list **lst, char *pre_line)
{
	char	*line;
	char	*tmp;
	size_t	len;

	tmp = ft_strchr(pre_line, '\n');
	len = (ft_strlen(pre_line) - ft_strlen(tmp) + 1);
	line = ft_substr(lst, pre_line, 0, len);
	if (!line)
		return (ft_free(lst, pre_line), NULL);
	return (line);
}

static char	*read_line(t_list **lst, int fd, char *pre_line)
{
	ssize_t	byte;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char *));
	if (!buffer)
		return (NULL);
	byte = 1;
	while (!ft_strchr(pre_line, '\n') && byte != 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == 0)
			break ;
		if (byte == -1)
			return (free(buffer), ft_free(lst, pre_line), NULL);
		buffer[byte] = '\0';
		if (!pre_line)
			pre_line = ft_strdup(lst, buffer);
		else
			pre_line = ft_strjoin(lst, pre_line, buffer);
		if (!pre_line)
			return (free(buffer), NULL);
	}
	return (free(buffer), pre_line);
}

char	*get_next_line(t_list **lst, int fd)
{
	static char	*pre_line[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	pre_line[fd] = read_line(lst, fd, pre_line[fd]);
	if (!pre_line[fd])
		return (NULL);
	line = clean_line(lst, pre_line[fd]);
	pre_line[fd] = update_line(lst, pre_line[fd]);
	return (line);
}
