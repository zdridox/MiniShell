/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:48:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 20:03:10 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	str1[] = "Hi, I'm a string";
	char	original[20];
	char	fake[20];

	strlcpy(original, str1, 9);
	ft_strlcpy(fake, str1, 9);
	printf("Original:\nstr1: %s\nstr2: %s\n", str1, original);
	printf("Fake:\nstr1: %s\nstr2: %s\n", str1, fake);
	return (0);
}
*/
