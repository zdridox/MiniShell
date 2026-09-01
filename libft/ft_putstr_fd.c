/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:50:21 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 11:11:46 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
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
	ft_putstr_fd("Happy evaluation!\n", fd);
	close(fd);
}
*/
