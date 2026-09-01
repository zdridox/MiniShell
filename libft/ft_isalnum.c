/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:46:16 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/20 14:52:29 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
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
		printf("%c - %d\n", c, ft_isalnum(c));
		c++;
	}
}
*/
