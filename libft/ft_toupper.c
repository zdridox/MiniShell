/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:12:45 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 10:36:15 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello 123, is I'm upper?";
	int		i;

	printf("Original: %s\n", str);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("Fake    : %s", str);
	return (0);
}
*/
/*
int	main(void)
{
	printf("%c", ft_toupper('a'));
	return (0);
}
*/
