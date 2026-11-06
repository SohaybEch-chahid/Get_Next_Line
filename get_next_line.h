/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:22:09 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/06 10:13:53 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXTILINE_H
# define GET_NEXTILINE_H

#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 100

char	*get_next_line(int fd);

#endif
