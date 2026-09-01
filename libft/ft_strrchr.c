/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/13 22:13:07 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Find the 'y' in this string, or this 'y'";

	printf("Find: %s", ft_strrchr(str, 'y'));
	return (0);
}
*/
