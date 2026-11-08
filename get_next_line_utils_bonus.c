/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 15:27:37 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/08 16:08:55 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	join = malloc(i + j + 1);
	if (!join)
		return (NULL);
	k = 0;
	j = 0;
	while (s1 && s1[j])
		join[k++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		join[k++] = s2[j++];
	join[k] = '\0';
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
	return (NULL);
}

t_fd	*get_fd_node(t_fd **head, int fd)
{
	t_fd	**link;
	t_fd	*node;

	link = head;
	while (*link)
	{
		if ((*link)->fd == fd)
			return (*link);
		link = &(*link)->next;
	}
	node = malloc(sizeof(t_fd));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->stash = NULL;
	node->next = NULL;
	*link = node;
	return (node);
}

void	remove_fd(t_fd **head, int fd)
{
	t_fd	**link;
	t_fd	*node;

	link = head;
	while (*link)
	{
		if ((*link)->fd == fd)
		{
			node = *link;
			*link = node->next;
			free(node->stash);
			free(node);
			return ;
		}
		link = &(*link)->next;
	}
}
