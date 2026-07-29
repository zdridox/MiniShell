/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:17:38 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/28 17:20:56 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	replace_quoted_wildcards_in_string(char *str)
{
	while (*str)
	{
		if (*str == '*')
			*str = QUOTED_WILDCARD;
		str++;
	}
}

static void	replace_qutoed_wildcards_in_word(t_word_part *word_parts)
{
	while (word_parts)
	{
		if (word_parts->type != PLAIN)
			replace_quoted_wildcards_in_string(word_parts->value);
		word_parts = word_parts->next;
	}
}

static char	*convert_word_to_pattern(t_word_part *word_parts)
{
	char	*pattern;
	int		pattern_length;
	int		pattern_index;
	int		string_length;

	pattern_length = get_word_length(word_parts);
	pattern = malloc(pattern_length + 1);
	if (!pattern)
		return (NULL);
	replace_qutoed_wildcards_in_word(word_parts);
	pattern_index = 0;
	while (word_parts)
	{
		string_length = ft_strlen(word_parts->value);
		ft_memcpy(pattern + pattern_index, word_parts->value, string_length);
		pattern_index += string_length;
		word_parts = word_parts->next;
	}
	pattern[pattern_length] = '\0';
	return (pattern);
}

bool	expand_wildcards_to_dynamic_string(t_word_part *word_parts,
		t_dynamic_string *dynamic_string)
{
	char	*pattern;

	pattern = convert_word_to_pattern(word_parts);
	if (!pattern)
		return (false);
	if (!expand_wildcard(pattern, dynamic_string))
		return (free(pattern), false);
	free(pattern);
	return (true);
}
