/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 00:57:34 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/08 16:22:48 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buffer(int fd, char *stash, char *buffer)
{
	char	*tmp;
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchar(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
		{
			free(stash);
			return (NULL);
		}
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
	{
		free(stash);
		return (NULL);
	}
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
	if (!stash[current])
	{
		free(stash);
		return (NULL);
	}
	current++;
	if (!stash[current])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strjoin(stash + current, NULL);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static t_fd	*head;
	t_fd		*node;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_fd_node(&head, fd);
	if (!node)
		return (NULL);
	node->stash = read_and_store(fd, node->stash);
	if (!node->stash)
	{
		remove_fd(&head, fd);
		return (NULL);
	}
	line = extract_line(node->stash);
	if (!line)
	{
		remove_fd(&head, fd);
		return (NULL);
	}
	node->stash = update_stash(node->stash);
	if (!node->stash)
		remove_fd(&head, fd);
	return (line);
}
