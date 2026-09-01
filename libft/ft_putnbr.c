/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:43:07 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/29 15:24:53 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	recursive_putnbr(size_t num, size_t *ret)
{
	if (num > 9)
	{
		recursive_putnbr(num / 10, ret);
	}
	*ret += ft_putchar(num % 10 + '0');
}

int	put_unsigned_int(unsigned int num)
{
	size_t	ret;

	ret = 0;
	recursive_putnbr(num, &ret);
	return (ret);
}

int	ft_putnbr(int num)
{
	size_t	unsigned_num;
	size_t	ret;

	ret = 0;
	if (num < 0)
	{
		unsigned_num = (long)num * -1;
		ret += ft_putchar('-');
	}
	else
		unsigned_num = num;
	recursive_putnbr(unsigned_num, &ret);
	return (ret);
}
