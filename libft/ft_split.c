/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:42:23 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/20 21:03:33 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	size_t	words_count;
	size_t	i;

	words_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			words_count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words_count);
}

static int	add_word(char const *word_start, size_t word_len, char **words_arr)
{
	char	*new_word;

	new_word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!new_word)
		return (-1);
	ft_memcpy(new_word, word_start, word_len);
	new_word[word_len] = '\0';
	*words_arr = new_word;
	return (0);
}

static char	*find_next_word(char const *str, char c, size_t *len)
{
	*len = 0;
	while (*str && *str == c)
		str++;
	while (*str && *str != c)
	{
		(*len)++;
		str++;
	}
	return ((char *)str - *len);
}

void	clear_allocated_mem(char **words_arr, int i)
{
	while (i >= 0)
	{
		free(words_arr[i]);
		i--;
	}
	free(words_arr);
}

char	**ft_split(char const *str, char c)
{
	char		**words_arr;
	char const	*word_start;
	size_t		word_len;
	int			i;

	words_arr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!words_arr)
		return (NULL);
	i = 0;
	while (*str)
	{
		word_start = find_next_word(str, c, &word_len);
		if (!*word_start)
			break ;
		if (add_word(word_start, word_len, &words_arr[i++]) != 0)
			return (clear_allocated_mem(words_arr, --i), NULL);
		str = word_start + word_len;
	}
	words_arr[i] = NULL;
	return (words_arr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "abs aaaa";
	char	c = ' ';
	char	**words_arr;
	size_t	i;
	
	printf("str: \"%s\"\nc = \'%c\'\n", str, c);
	words_arr = ft_split(str, c);
	printf("Words:\n");
	i = 0;
	while (words_arr[i] != NULL)
		printf("%s\n", words_arr[i++]);
}
*/
