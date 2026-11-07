/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 09:59:02 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 17:26:41 by sech-cha         ###   ########.fr       */
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
int				ft_strlen(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchar(char *s, int c);
void			remove_fd(t_fd **head, int fd);
t_fd			*find_fd(t_fd *head, int fd);
t_fd			*new_fd(int fd);
t_fd			*lst_add_back_fd(t_fd *head, t_fd *new_node);
char			*ft_strdup(const char *s);
t_fd	*get_fd_node(t_fd **head, int fd);

#endif
