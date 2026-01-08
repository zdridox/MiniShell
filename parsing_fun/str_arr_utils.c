/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:00:43 by mzdrodow          #+#    #+#             */
/*   Updated: 2026/01/09 00:33:04 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_fun.h"

// void	str_arr_print(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		ft_printf("%s\n", arr[i]);
// 		i++;
// 	}
// }

void	str_arr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	str_arr_copy(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
}

char	**str_arr_resize(char **arr, int new_size)
{
	char	**new_arr;

	new_arr = malloc(new_size * sizeof(char *));
	if (!new_arr)
		return (NULL);
	str_arr_copy(new_arr, arr);
	str_arr_free(arr);
	return (new_arr);
}

int	str_arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
char	*ft_strdup(char *src)
{
	int		size;
	int		i;
	char	*dup;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	dup = malloc(size + 1);
	if (!dup)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}