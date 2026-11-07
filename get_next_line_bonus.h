/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 09:59:02 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/07 11:40:20 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd
{
	int			fd;
	char		*stash;
	struct s_fd	*next;
}				t_fd;

# define BUFFER_SIZE 100

# define OPEN_MAX 1024

char			*get_next_line_bonus(int fd);

#endif
