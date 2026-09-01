/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:53 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 20:20:15 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	make_map(unsigned long long *map, char const *set)
{
	size_t	i;

	ft_memset(map, 0, sizeof(unsigned long long) * 2);
	i = 0;
	while (set[i])
	{
		map[(unsigned char)set[i] / 64]
			|= (1ULL << ((unsigned char)set[i] % 64));
		i++;
	}
}

static const char	*find_start(char const *str, unsigned long long *map)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(map[(unsigned char)str[i] / 64]
				& (1ULL << ((unsigned char)str[i] % 64))))
		{
			break ;
		}
		i++;
	}
	return (&str[i]);
}

static const char	*find_end(char const *str, unsigned long long *map,
	size_t str_len)
{
	while (str_len > 0)
	{
		str_len--;
		if (!(map[(unsigned char)str[str_len] / 64]
				& (1ULL << ((unsigned char)str[str_len] % 64))))
		{
			break ;
		}
	}
	return (&str[str_len]);
}

char	*ft_strtrim(char const *str, char const *set)
{
	unsigned long long	map[2];
	size_t				trimed_len;
	char				*trimed_str;
	const char			*start;
	const char			*end;

	if (str == NULL)
		return (NULL);
	if (*str == '\0')
		return (ft_strdup(""));
	make_map(map, set);
	start = find_start(str, map);
	if (*start == '\0')
		return (ft_strdup(""));
	end = find_end(str, map, ft_strlen(str));
	if (start > end)
		return (ft_strdup(""));
	trimed_str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trimed_str)
		return (NULL);
	trimed_len = end - start + 1;
	ft_memcpy(trimed_str, start, trimed_len);
	trimed_str[trimed_len] = '\0';
	return (trimed_str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "   Hello    ";
	char	set[] = " ";
	char	*trimed_str;

	printf("str: \"%s\"\nset: \"%s\"\n", str, set);
	trimed_str = ft_strtrim(str, set);
	printf("trimed_str: \"%s\"\n", trimed_str);
	free(trimed_str);
	trimed_str = NULL;
	return (0);
}
*/
