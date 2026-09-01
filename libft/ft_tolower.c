/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:26:29 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 10:36:58 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
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
	printf("%c", ft_tolower('A'));
	return (0);
}
*/
