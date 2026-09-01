/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:03:48 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/16 20:53:44 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static unsigned int	get_total_len(va_list args, unsigned int count)
{
	unsigned int	total_len;
	unsigned int	i;
	char			*current_str;

	i = 0;
	total_len = 0;
	while (i < count)
	{
		current_str = va_arg(args, char *);
		if (!current_str)
			i++;
		total_len += ft_strlen(current_str);
		i++;
	}
	return (total_len);
}

static char	*join_strings(va_list args, unsigned int count,
		unsigned int total_len)
{
	unsigned int	result_str_iter;
	unsigned int	strings_iter;
	char			*joined_str;
	char			*current_str;

	strings_iter = 0;
	result_str_iter = 0;
	joined_str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!joined_str)
		return (NULL);
	while (strings_iter < count)
	{
		current_str = va_arg(args, char *);
		strings_iter++;
		if (current_str == NULL)
			continue ;
		while (*current_str)
		{
			joined_str[result_str_iter] = *current_str;
			result_str_iter++;
			current_str++;
		}
	}
	joined_str[result_str_iter] = '\0';
	return (joined_str);
}

char	*ft_strjoin_many(unsigned int count, ...)
{
	va_list			args;
	unsigned int	total_len;
	char			*result;

	va_start(args, count);
	total_len = get_total_len(args, count);
	va_end(args);
	va_start(args, count);
	result = join_strings(args, count, total_len);
	va_end(args);
	return (result);
}
