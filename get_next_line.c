/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:21:14 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 17:19:20 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, char *stash, char *buffer)
{
	char	*tmp;
	int		bytes;

	bytes = 1;
	while (!ft_strchar(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (free(stash), NULL);
		free(stash);
		stash = tmp;
	}
	return (stash);
}

char	*read_and_store(int fd, char *stash)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	stash = read_buffer(fd, stash, buffer);
	free(buffer);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		len;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stash(char *stash)
{
	char	*new_stash;
	int		current;

	current = 0;
	while (stash[current] && stash[current] != '\n')
		current++;
	if (stash[current] == '\0')
		return (free(stash), NULL);
	current++;
	if (!stash[current])
		return (free(stash), NULL);
	new_stash = ft_strdup(stash + current);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_store(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
