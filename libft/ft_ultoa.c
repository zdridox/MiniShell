/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 17:43:12 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/30 18:07:04 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_digits(unsigned long num)
{
	unsigned int	digits_num;

	digits_num = 0;
	while (num != 0)
	{
		num /= 10;
		digits_num++;
	}
	return (digits_num);
}

// Converts an unsigned long integer to a string representation.
char	*ft_ultoa(unsigned long num)
{
	unsigned int	digits_num;
	char			*ascii_num;
	int				i;

	if (num == 0)
		return (ft_strdup("0"));
	digits_num = count_digits(num);
	ascii_num = (char *)malloc(sizeof(char) * (digits_num + 1));
	if (!ascii_num)
		return (NULL);
	i = digits_num;
	ascii_num[i--] = '\0';
	while (i >= 0)
	{
		ascii_num[i--] = num % 10 + '0';
		num /= 10;
	}
	return (ascii_num);
}
