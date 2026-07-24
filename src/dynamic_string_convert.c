/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string_convert.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:31:35 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/24 17:53:59 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static size_t	count_strings_in_dynamic_string(t_dynamic_string *dynamic_string)
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

