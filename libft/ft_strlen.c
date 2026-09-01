/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:40:10 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 20:03:35 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}
/*
#include <stdio.h>

int	main()
{
	char s[] = "Hi!";

	printf("str: '%s', len: %lu", s, ft_strlen(s));
}
*/
