/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:47:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/14 21:22:09 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*c_str1;
	unsigned char	*c_str2;

	if (str1 == NULL || str2 == NULL)
		return (0);
	c_str1 = (unsigned char *)str1;
	c_str2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (c_str1[i] != c_str2[i])
			return ((unsigned char)c_str1[i] - (unsigned char)c_str2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "Kukulala";
	char	str2[] = "Kukulala";

	printf("%d", ft_memcmp(str1, str2, 5));
	return (0);
}
*/
