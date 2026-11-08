/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:08:09 by passunca          #+#    #+#             */
/*   Updated: 2026/11/08 18:28:43 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../get_next_line.h"
#include <fcntl.h>
# include <stdio.h>

int main(void)
{
	char	*line;
	int		fd;

	fd = open("../files/big_line_no_nl.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	return (0);
}
