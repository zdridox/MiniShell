/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:28:14 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/24 17:31:07 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

bool	append_int_to_dynamic_string(int num, t_dynamic_string *dynamic_string)
{
	unsigned char	size;
	unsigned char	is_negative;
	char			ascii_num[12];
	long			long_num;
	int				i;

	if (num == 0)
		return (add_char_to_dynamic_string('0', dynamic_string));
	is_negative = check_is_negative(num, &long_num);
	size = count_digits(num) + is_negative;
	i = size;
	ascii_num[i--] = '\0';
	while (i >= 0)
	{
		ascii_num[i--] = long_num % 10 + '0';
		long_num /= 10;
	}
	if (is_negative)
		ascii_num[0] = '-';
	return (add_n_chars_to_dynamic_string(ascii_num, size, dynamic_string));
}
