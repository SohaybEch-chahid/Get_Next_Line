/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sech-cha <sech-cha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 19:43:45 by sech-cha          #+#    #+#             */
/*   Updated: 2026/11/08 18:28:55 by sech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

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
