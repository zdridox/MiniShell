/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:27:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 19:47:11 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
/*
#include <stdio.h>

int	main(void)
{
	int	fd;
	fd = creat("newfile.txt", 0644);
	if (fd == -1)
	{
		printf("Error creating file\n");
		return (1);
	}
	ft_putchar_fd('z', fd);
	close(fd);
}
*/
