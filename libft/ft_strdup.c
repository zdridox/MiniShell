/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:22:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/13 22:33:56 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*duplicate;
	size_t	i;

	if (str == NULL)
		return (NULL);
	duplicate = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (duplicate == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "Happy evaluation!";
	char 	*str2;

	str2 = ft_strdup(str1);
	printf("str1 = %s\nstr2 = %s\n", str1, str2);
	return (0);
}
*/
