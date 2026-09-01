/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:43:37 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/13 18:41:02 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	if (size <= dst_len)
		return (src_len + size);
	while (size > dst_len + i + 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
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
