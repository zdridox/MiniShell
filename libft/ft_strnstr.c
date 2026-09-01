/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:33:35 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/13 22:30:07 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (big == NULL || little == NULL)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)&big[i]);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
			j++;
		else
		{
			i -= j;
			j = 0;
		}
		if (little[j] == '\0')
			return ((char *)&big[i - j + 1]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	big[] = "Find the 'y' in this string";
	char	little[] = "F";

	printf("Find: %s", ft_strnstr(big, little, 99));
	return (0);
}
*/
