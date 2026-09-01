/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:30:32 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 21:11:25 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	c_c;
	unsigned char	*c_str;

	if (str == NULL)
		return (NULL);
	i = 0;
	c_c = c;
	c_str = (unsigned char *)str;
	while (i < n)
	{
		if (c_str[i] == c_c)
			return (&c_str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Find the 'y' in this string";

	printf("Find: %s", (char *)ft_memchr(str, '3', 99));
	return (0);
}
*/
