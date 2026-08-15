/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:29:26 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 16:27:56 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	init_dynamic_string(t_dynamic_string *dynamic_string,
		size_t inital_cappacity)
{
	dynamic_string->size = 0;
	dynamic_string->capacity = inital_cappacity;
	dynamic_string->string = malloc(dynamic_string->capacity * sizeof(char));
	if (dynamic_string->string == NULL)
		return (false);
	return (true);
}

bool	resize_dynamic_string(t_dynamic_string *dynamic_string,
		size_t new_capacity)
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

bool	add_string_to_dynamic_string(char *string,
		t_dynamic_string *dynamic_string)
{
	size_t	string_len;
	size_t	needed_capacity;

	string_len = (size_t)ft_strlen(string);
	needed_capacity = dynamic_string->size + string_len + 1;
	if (needed_capacity > dynamic_string->capacity)
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
	}
	ft_memcpy(dynamic_string->string + dynamic_string->size, string,
		string_len);
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

bool	add_n_chars_to_dynamic_string(char *string, size_t string_len,
		t_dynamic_string *dynamic_string)
{
	size_t	needed_capacity;

	if (string_len == 0 || string == NULL)
		return (true);
	needed_capacity = dynamic_string->size + string_len;
	if (dynamic_string->capacity > needed_capacity)
		ft_memcpy(dynamic_string->string + dynamic_string->size, string,
			string_len);
	else
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
		ft_memcpy(dynamic_string->string + dynamic_string->size, string,
			string_len);
	}
	dynamic_string->size += string_len;
	return (true);
}
