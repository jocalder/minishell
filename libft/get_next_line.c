/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:43:33 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/16 18:08:00 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*update_line(char *pre_line)
{
	char	*next_line;
	char	*tmp;

	tmp = ft_strchr(pre_line, '\n');
	next_line = ft_substr(tmp, 1, ft_strlen(tmp));
	if (next_line && !*next_line)
		return (free(pre_line), free(next_line), NULL);
	return (free(pre_line), next_line);
}

static char	*clean_line(char *pre_line)
{
	char	*line;
	char	*tmp;
	size_t	len;

	tmp = ft_strchr(pre_line, '\n');
	len = (ft_strlen(pre_line) - ft_strlen(tmp) + 1);
	line = ft_substr(pre_line, 0, len);
	if (!line)
		return (free(pre_line), NULL);
	return (line);
}

static char	*read_line(int fd, char *pre_line)
{
	ssize_t	byte;
	char	*buffer;

	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byte = 1;
	while (!ft_strchr(pre_line, '\n') && byte != 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == 0)
			break ;
		if (byte == -1)
			return (free(buffer), free(pre_line), NULL);
		buffer[byte] = '\0';
		if (!pre_line)
			pre_line = ft_strdup(buffer);
		else
			pre_line = ft_strjoin(pre_line, buffer);
		if (!pre_line)
			return (free(buffer), NULL);
	}
	return (free(buffer), pre_line);
}

char	*get_next_line(int fd)
{
	static char	*pre_line[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	pre_line[fd] = read_line(fd, pre_line[fd]);
	if (!pre_line[fd])
		return (NULL);
	line = clean_line(pre_line[fd]);
	pre_line[fd] = update_line(pre_line[fd]);
	return (line);
}
