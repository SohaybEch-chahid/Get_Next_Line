/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 09:59:02 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 19:23:29 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fd
{
	int			fd;
	char		*stash;
	struct s_fd	*next;
}				t_fd;

char			*get_next_line(int fd);

char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchar(char *s, int c);

t_fd			*get_fd_node(t_fd **head, int fd);
void			remove_fd(t_fd **head, int fd);

#endif
