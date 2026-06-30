/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:29:26 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/06/30 21:39:58 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	init_dynamic_string(t_dynamic_string *dynamic_string, size_t inital_cappacity)
{
	dynamic_string->size = 0;
	dynamic_string->capacity = inital_cappacity;
	dynamic_string->string = malloc(dynamic_string->capacity * sizeof(char));
	if (dynamic_string->string == NULL)
		return (false);
	return (true);
}

bool	resize_dynamic_string(t_dynamic_string *dynamic_string, size_t new_capacity)
{
	char	*new_string;

	new_string = malloc(new_capacity * sizeof(char));
	if (!new_string)
		return (false);
	ft_memcpy(new_string, dynamic_string->string, dynamic_string->size);
	free(dynamic_string->string);
	dynamic_string->string = new_string;
	dynamic_string->capacity = new_capacity;
	return (true);
}

bool	add_string_to_dynamic_string(char *string, t_dynamic_string *dynamic_string)
{
	size_t	string_len;
	size_t	needed_capacity;
	
	string_len = (size_t)ft_strlen(string);
	needed_capacity = dynamic_string->size + string_len + 1;
	if (dynamic_string->capacity > needed_capacity)
		ft_memcpy(dynamic_string->string + dynamic_string->size, string, string_len);
	else
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
		ft_memcpy(dynamic_string->string + dynamic_string->size, string, string_len);
	}
	dynamic_string->string[dynamic_string->size + string_len] = '\0';
	dynamic_string->size += string_len + 1;
	return (true);
}

bool	add_char_to_dynamic_string(char c, t_dynamic_string *dynamic_string)
{
	size_t	needed_capacity;

	needed_capacity = dynamic_string->size + 1;
	if (dynamic_string->capacity > needed_capacity)
		dynamic_string->string[dynamic_string->size] = c;
	else
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
		dynamic_string->string[dynamic_string->size] = c;
	}
	dynamic_string->size += 1;
	return (true);
}

bool	add_n_chars_to_dynamic_string(char *string, size_t string_len, t_dynamic_string *dynamic_string)
{
	size_t	needed_capacity;
	
	if (string_len == 0)
		return (true);
	needed_capacity = dynamic_string->size + string_len;
	if (dynamic_string->capacity > needed_capacity)
		ft_memcpy(dynamic_string->string + dynamic_string->size, string, string_len);
	else
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
		ft_memcpy(dynamic_string->string + dynamic_string->size, string, string_len);
	}
	dynamic_string->size += string_len;
	return (true);
}

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

size_t	count_strings_in_dynamic_string(t_dynamic_string *dynamic_string)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < dynamic_string->size)
	{
		if (dynamic_string->string[i] == '\0')
			count++;
		i++;
	}
	return (count);
}

char	**convert_dynamic_string_to_str_arr(t_dynamic_string *dynamic_string)
{
	char	**str_arr;
	size_t	str_count;
	size_t	i;
	size_t	j;

	if (dynamic_string->size == 0)
		return (NULL);
	str_count = count_strings_in_dynamic_string(dynamic_string);
	str_arr = malloc((str_count + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < str_count)
	{
		str_arr[i] = &(dynamic_string->string[j]);
		j += ft_strlen(&(dynamic_string->string[j])) + 1;
		i++;
	}
	str_arr[str_count] = NULL;
	return (str_arr);
}
