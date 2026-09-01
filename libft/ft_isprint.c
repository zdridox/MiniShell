/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:28:55 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 09:57:24 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int	main()
{
	unsigned char c;
	c = 0;
	while (c < 255)
	{
		printf("%c - %d\n", c, ft_isprint(c));
		c++;
	}
}
*/
