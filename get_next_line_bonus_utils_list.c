/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils_list.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:34:11 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 17:34:24 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
