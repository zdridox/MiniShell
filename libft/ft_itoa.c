/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:52:49 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/08 14:44:57 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int num)
{
	size_t	digits_num;

	digits_num = 0;
	while (num != 0)
	{
		num /= 10;
		digits_num++;
	}
	return (digits_num);
}

static unsigned char	check_is_negative(int num, long *long_num)
{
	unsigned char	is_negative;

	if (num < 0)
	{
		*long_num = (long)num * -1;
		is_negative = 1;
	}
	else
	{
		*long_num = (long)num;
		is_negative = 0;
	}
	return (is_negative);
}

char	*ft_itoa(int num)
{
	unsigned char	digits_num;
	char			*ascii_num;
	unsigned char	is_negative;
	long			long_num;
	int				i;

	if (num == 0)
		return (ft_strdup("0"));
	digits_num = count_digits(num);
	is_negative = check_is_negative(num, &long_num);
	ascii_num = (char *)malloc(sizeof(char) * digits_num + is_negative + 1);
	if (!ascii_num)
		return (NULL);
	i = digits_num + is_negative;
	ascii_num[i--] = '\0';
	while (i >= 0)
	{
		ascii_num[i--] = long_num % 10 + '0';
		long_num /= 10;
	}
	if (is_negative)
		ascii_num[0] = '-';
	return (ascii_num);
}
/*
#include <stdio.h>

int	main(void)
{
  int           num;
  unsigned int  i;

  int tests[] = {0, 42, -132, 45600, INT_MIN, INT_MAX};
  i = 0;
  while (i <= 5)
  {
    printf("== Test %d ==\n", i + 1);
    printf("int = %d\nstr = %s\n", tests[i], ft_itoa(tests[i]));
    i++;
  }
	return (0);
}
*/
