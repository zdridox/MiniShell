/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:47:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/30 17:05:00 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	recursive_puthex(size_t num, size_t *ret, const char *base_str)
{
	if (num > 15)
	{
		recursive_puthex(num / 16, ret, base_str);
	}
	*ret += ft_putchar(base_str[num % 16]);
}

int	ft_puthex(size_t num, const char *base_str)
{
	size_t	ret;

	ret = 0;
	recursive_puthex(num, &ret, base_str);
	return (ret);
}
