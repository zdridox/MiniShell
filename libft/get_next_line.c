/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:46:05 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/11/15 17:46:11 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*remainder;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash || !stash[0])
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	remainder = extract_remainder(stash);
	free(stash);
	stash = remainder;
	return (line);
}

/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error with opening file\n");
		return (-1);
	}
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
}
*/
