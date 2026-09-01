/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:49:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/29 18:33:42 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	recursive_put_address(unsigned long num_address, size_t *ret,
			const char *base_str)
{
	if (num_address > 15)
	{
		recursive_put_address(num_address / 16, ret, base_str);
	}
	*ret += ft_putchar(base_str[num_address % 16]);
}

int	ft_put_address(unsigned long num_address, const char *base_str)
{
	size_t	ret;

	ret = 0;
	if (!num_address)
		return (ft_putstr("(nil)"));
	ret += ft_putstr("0x");
	recursive_put_address(num_address, &ret, base_str);
	return (ret);
}
