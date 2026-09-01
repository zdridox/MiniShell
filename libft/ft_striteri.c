/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:08:28 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 11:09:56 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*fun)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		fun(i, &str[i]);
		i++;
	}
}
/*
void	my_fun(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = '*';
}

int	main(void)
{
	char	str[] = "Happy evaluation!!!";

	printf("str: \"%s\"\n", str);
	ft_striteri(str, my_fun);
	printf("modified_str: \"%s\"\n", str);
}
*/
