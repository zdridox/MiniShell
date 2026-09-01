/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:28:39 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 20:57:45 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	size_t				i;
	const unsigned char	*c_src;
	unsigned char		*c_dest;

	c_src = src;
	c_dest = dest;
	i = 0;
	if (c_src + num >= c_dest && c_src < c_dest)
	{
		while (i < num)
		{
			c_dest[num - i - 1] = c_src[num - i - 1];
			i++;
		}
	}
	else
	{
		while (i < num)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "-orem ipsum dolor sit a";

	printf("Str: %s\n", str);
	ft_memmove(&str[4], &str[6], 6);
	printf("Str: %s\n", str);
	return (0);
}
*/
