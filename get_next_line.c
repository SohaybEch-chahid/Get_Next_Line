/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:21:14 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 00:56:55 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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
    int i;

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
            free (stash);
			return (NULL);
		}
        if (bytes == 0)
            break;
        buffer[bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
		{
			free(buffer);
            free (stash);
			return (NULL);
		}
		free(stash);
		stash = tmp;
	}
    free (buffer);
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
    char *new_stash;
	int	current;
    int i;

    current = 0;
	while (stash[current] && stash[current] != '\n')
		current++;
    if (stash[current] == '\0')
    {
        free (stash);
        return NULL;
    }
    current++;
    if (!stash[current])
    {
        free (stash);
        return NULL;
    }
    new_stash = malloc (ft_strlen(stash + current) + 1);
    if (!new_stash)
    {
        free (stash);
        return NULL;
    }
    i = 0;
    while (stash[current])
        new_stash[i++] = stash[current++];
    new_stash[i] = '\0';
    free (stash);
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

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("error");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
