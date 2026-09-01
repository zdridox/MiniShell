/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:18:20 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/22 19:15:47 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_putnbr(long num, int fd)
{
	if (num < 0)
	{
		num *= -1;
		ft_putchar_fd('-', fd);
	}
	if (num > 9)
	{
		recursive_putnbr(num / 10, fd);
	}
	ft_putchar_fd(num % 10 + '0', fd);
}

void	ft_putnbr_fd(int num, int fd)
{
	long	long_num;

	long_num = (long)num;
	recursive_putnbr(long_num, fd);
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
	ft_putnbr_fd(12345, fd);
	close(fd);
}
*/
