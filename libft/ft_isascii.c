/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:21:27 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 09:56:45 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	int	c;		

	c = -10;
	while (c <= 300)
	{
		printf("%d - %d\n", c, ft_isascii(c));
		c++;
	}
	return (0);
}
*/
