/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:21:05 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 19:35:40 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*c;

	if (ptr == NULL)
		return (NULL);
	c = ptr;
	i = 0;
	while (i < num)
	{
		c[i] = value;
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hi, my friend!";

	printf("originale: %s\n", str);
	ft_memset(str, '*', 5);
	printf("fake: %s\n", str);
	return (0);
}
*/
