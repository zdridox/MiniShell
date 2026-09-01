/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:48:10 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 19:25:01 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	size_t			i;
	unsigned char	*c_ptr;

	if (ptr == NULL)
		return ;
	c_ptr = ptr;
	i = 0;
	while (i < n)
	{
		c_ptr[i++] = '\0';
	}
}
/*
#include <unistd.h>

int	main(void)
{
	char	str[] = "Hello";
	int		i;	

	ft_bzero(str + 2, 2);
	i = 0;
	while (i < 5)
	{
		write(1, &str[i], 1);
		i++;
	}
	return (0);
}
*/
