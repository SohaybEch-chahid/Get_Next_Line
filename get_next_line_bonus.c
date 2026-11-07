/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 00:57:34 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 14:56:32 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}

char	*ft_strchar(char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (s && (char)c == '\0')
		return (&s[i]);
	return (NULL);
}

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
void	remove_fd(t_fd **head, int fd)
{
	t_fd	*current;
	t_fd	*tmp;

	if (!head || !*head)
		return ;
	current = *head;
	if (current->fd == fd)
	{
		tmp = current;
		*head = current->next;
		free(tmp->stash);
		free(tmp);
		return ;
	}
	while (current->next)
	{
		if (current->next->fd == fd)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp->stash);
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

t_fd	*find_fd(t_fd *head, int fd)
{
	t_fd	*node;

	if (!head)
		return (NULL);
	node = head;
	while (node)
	{
		if (node->fd == fd)
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

t_fd	*new_fd(int fd)
{
	t_fd	*node;

	node = malloc(sizeof(t_fd));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->stash = NULL;
	node->next = NULL;
	return (node);
}

t_fd	*lst_add_back_fd(t_fd *head, t_fd *new)
{
	t_fd	*node;

	if (!head)
		return (new);
	node = head;
	while (node->next)
	{
		node = node->next;
	}
	node->next = new;
	return (head);
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

int	main(void)
{
	char	*line;

	int fd1, fd2, fd3;
	fd1 = open("text1.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("error1");
		return (1);
	}
	fd2 = open("text2.txt", O_RDONLY);
	if (fd2 == -1)
	{
		printf("error2");
		return (1);
	}
	fd3 = open("text3.txt", O_RDONLY);
	if (fd3 == -1)
	{
		printf("error3");
		return (1);
	}
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd3);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd3);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	/*
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}*/
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
