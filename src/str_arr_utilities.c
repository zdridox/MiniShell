/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:20:34 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/24 19:53:21 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h" // narazie spada
#include "../libft/libft.h"

void free_str_arr(char **str_arr)
{
	unsigned int i;

	i = 0;
	if (!str_arr)
		return;
	while (str_arr[i])
	{
		free(str_arr[i++]);
	}
	free(str_arr);
}

int str_arr_len(char **str_arr)
{
	unsigned int len;

	if (!str_arr)
		return (0);
	len = 0;
	while (str_arr[len])
	{
		len++;
	}
	return (len);
}

char **copy_arr(char **old_str_arr)
{
	char **new_str_arr;
	unsigned int new_arr_size;
	unsigned int i;

	if (!old_str_arr)
		return (NULL);
	new_arr_size = (str_arr_len(old_str_arr) + 1) * sizeof(char *);
	new_str_arr = (char **)malloc(new_arr_size);
	if (!new_str_arr)
		return (NULL);
	i = 0;
	while (old_str_arr[i])
	{
		new_str_arr[i] = ft_strdup(old_str_arr[i]);
		if (!new_str_arr[i])
		{
			free_str_arr(new_str_arr);
			return (NULL);
		}
		i++;
	}
	new_str_arr[i] = NULL;
	return (new_str_arr);
}

// char **resize_str_arr(char **old_str_arr, int new_size) // possible leak? // cos mieszalem
// {
// 	unsigned int i;
// 	char **new_str_arr;

// 	if (new_size < str_arr_len(old_str_arr))
// 	{
// 		return (NULL);
// 	}
// 	new_str_arr = (char **)malloc(new_size * sizeof(char *));
// 	if (!new_str_arr)
// 		return (NULL);
// 	i = 0;
// 	while (old_str_arr[i])
// 	{
// 		new_str_arr[i] = old_str_arr[i];
// 		i++;
// 	}
// 	new_str_arr[i] = NULL;
// 	free(old_str_arr);
// 	return (new_str_arr);
// }

// char **resize_str_arr(char **old_str_arr, int new_size)
// {
// 	int i;
// 	char **new_arr;

// 	if (!old_str_arr)
// 	{
// 		new_arr = malloc(sizeof(char *) * 2);
// 		new_arr[0] = NULL;
// 		return (new_arr);
// 	}
// 	i = 0;
// 	new_arr = malloc(sizeof(char *) * new_size + 1);
// 	while (old_str_arr[i])
// 	{
// 		new_arr[i] = ft_strdup(old_str_arr[i]);
// 		++i;
// 	}
// 	new_arr[i] = NULL;
// 	free_str_arr(old_str_arr);
// 	return (new_arr);
// }

char **resize_str_arr(char **old_str_arr, int new_size)
{
	int i;
	char **new_arr;

	// new_size is the number of string elements, so add 1 for NULL terminator.
	new_arr = malloc(sizeof(char *) * (new_size + 1));
	if (!new_arr)
	{
		free_str_arr(old_str_arr); // Free old array on allocation failure
		return (NULL);
	}
	i = 0;
	if (old_str_arr)
	{
		while (old_str_arr[i] && i < new_size)
		{
			new_arr[i] = ft_strdup(old_str_arr[i]);
			// It's good practice to check ft_strdup's return value
			i++;
		}
	}
	// Set the rest of the pointers, including the last one, to NULL.
	while (i <= new_size)
	{
		new_arr[i] = NULL;
		i++;
	}
	if (old_str_arr)
		free_str_arr(old_str_arr);
	return (new_arr);
}

char **add_back_str_arr(char **str_arr, char *new_element)
{
	char **new_str_arr;
	int i;

	new_str_arr = (char **)malloc((str_arr_len(str_arr) + 2) * sizeof(char *));
	if (!str_arr)
	{
		new_str_arr[0] = new_element;
		new_str_arr[1] = NULL;
		return (free_str_arr(str_arr), new_str_arr);
	}
	if (!new_str_arr)
		return (free_str_arr(str_arr), NULL);
	i = 0;
	while (str_arr[i])
	{
		new_str_arr[i] = ft_strdup(str_arr[i]);
		i++;
	}
	new_str_arr[i] = new_element;
	new_str_arr[i + 1] = NULL;
	return (free_str_arr(str_arr), new_str_arr);
}

void print_str_arr(char **str_arr)
{
	int i;

	i = 0;
	if (!str_arr)
		return;
	while (str_arr[i])
	{
		ft_putstr(str_arr[i++]);
		ft_putchar('\n');
	}
}
