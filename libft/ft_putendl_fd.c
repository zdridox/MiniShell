/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:01:53 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 11:12:37 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
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
	ft_putendl_fd("Happy evaluation!", fd);
	close(fd);
}
*/
