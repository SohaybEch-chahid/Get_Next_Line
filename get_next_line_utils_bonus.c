/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 15:27:37 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 15:35:20 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_fd	*lst_add_back_fd(t_fd *head, t_fd *new_node)
{
	t_fd	*node;

	if (!head)
		return (new_node);
	node = head;
	while (node->next)
	{
		node = node->next;
	}
	node->next = new_node;
	return (head);
}
