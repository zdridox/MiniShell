/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:12:44 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/07 14:12:06 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "tokenizer.h"

static bool	expand_word_to_dynamic_string(t_word_part *word_parts,
		t_dynamic_string *dynamic_string)
{
	while (word_parts)
	{
		if (!add_n_chars_to_dynamic_string(word_parts->value,
				ft_strlen(word_parts->value), dynamic_string))
			return (false);
		word_parts = word_parts->next;
	}
	if (!add_char_to_dynamic_string('\0', dynamic_string))
		return (false);
	return (true);
}

int	get_word_length(t_word_part *word_parts)
{
	int	length;

	length = 0;
	while (word_parts)
	{
		length += ft_strlen(word_parts->value);
		word_parts = word_parts->next;
	}
	return (length);
}

static bool	is_wildcard_present_in_word(t_word_part *word_parts)
{
	while (word_parts)
	{
		if (word_parts->type == PLAIN
			&& ft_strchr(word_parts->value, '*') != NULL)
			return (true);
		word_parts = word_parts->next;
	}
	return (false);
}

static bool	expand_one_word(t_word *word, t_dynamic_string *argv_string)
{
	if (is_wildcard_present_in_word(word->word_parts))
		return ((expand_wildcards_to_dynamic_string(word->word_parts,
					argv_string)));
	return (expand_word_to_dynamic_string(word->word_parts, argv_string));
}

char	**expand_to_argv(t_word *words, t_shell *shell)
{
	t_dynamic_string	argv_string;
	char				**argv;

	if (!words || !shell)
		return (NULL);
	if (!expand_environment_variables(words, shell))
		return (NULL);
	if (!init_dynamic_string(&argv_string, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (NULL);
	while (words)
	{
		if (!expand_one_word(words, &argv_string))
		{
			free(argv_string.string);
			return (NULL);
		}
		words = words->next;
	}
	argv = convert_dynamic_string_to_str_arr(&argv_string);
	return (argv);
}
