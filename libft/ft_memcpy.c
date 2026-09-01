/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:01:25 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 19:32:57 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t				i;
	const unsigned char	*c_src;
	unsigned char		*c_dest;

	if (dest == NULL || src == NULL)
		return (dest);
	c_src = src;
	c_dest = dest;
	i = 0;
	while (i < num)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "Hello my friend";
	char	str2[] = "Hello my enemy!";

	printf("Str1: %s\nStr2: %s\n-------\n", str1, str2);
	ft_memcpy(&str2[9], &str1[9], 6);
	printf("Str1: %s\nStr2: %s\n", str1, str2);
	return (0);
}
*/
