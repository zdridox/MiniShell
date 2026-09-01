/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 21:04:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/20 15:10:23 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			total_bytes;
	size_t			size_max;

	size_max = -1;
	if (size != 0 && nmemb > size_max / size)
		return (NULL);
	total_bytes = nmemb * size;
	ptr = (unsigned char *)malloc(total_bytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	char	*ptr;
	size_t	size;
	size_t	nmemb;
	size_t	i;

	size = SIZE_MAX;
	nmemb = 1;
	ptr = (char *)ft_calloc(nmemb, size);
	if (ptr != NULL)
	{
		i = 0;
		while (i < nmemb)
		{
			if (ptr[i++] == '\0')
				printf("\\0");
			else
				exit(0);
		}
	}
	else
		printf("NULL");
	return (0);
}
*/
