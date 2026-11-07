/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 00:57:34 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 15:36:33 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_store(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	bytes = 1;
	while (!ft_strchar(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = tmp;
	}
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
	int		node;
	int		i;

	node = 0;
	while (stash[node] && stash[node] != '\n')
		node++;
	if (stash[node] == '\0')
	{
		free(stash);
		return (NULL);
	}
	node++;
	if (!stash[node])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash + node) + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (stash[node])
		new_stash[i++] = stash[node++];
	new_stash[i] = '\0';
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
	node = find_fd(head, fd);
	if (!node)
	{
		node = new_fd(fd);
		if (!node)
			return (NULL);
		head = lst_add_back_fd(head, node);
	}
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
