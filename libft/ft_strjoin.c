/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:05:45 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/13 19:08:51 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	str_len;
	char	*str;
	size_t	i;
	size_t	j;

	str_len = ft_strlen(str1) + ft_strlen(str2);
	str = (char *)malloc(sizeof(char) * str_len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		str[i] = str2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "Happy ";
	char	str2[] = "evaluation!!!";
	char	*str;

	str = ft_strjoin(str1, str2);
	printf("str1:%s\n", str1);
	printf("str2:%s\n", str2);
	printf("str :%s\n", str);
	return (0);
}
*/
