/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:25:19 by maxim             #+#    #+#             */
/*   Updated: 2026/04/28 16:25:24 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static bool	add_word_part_back(t_word_part **current_part, t_word_part_type type, char *value)
{
	t_word_part	*new_part;

	new_part = malloc(sizeof(t_word_part));
	if (!new_part)
		return (false);
	new_part->type = type;
	new_part->value = value;
	new_part->next = NULL;
	if (*current_part)
		(*current_part)->next = new_part;
	*current_part = new_part;
	return (true);
}

static bool	add_plain_word_part(t_word_part **current_part, char *input, int *i)
{
	int		part_len;
	char	*plain_value;

	part_len = get_plain_part_length(input, *i);
	plain_value = ft_substr(input, *i, part_len);
	if (!plain_value)
		return (false);
	if (!add_word_part_back(current_part, PLAIN, plain_value))
	{
		free(plain_value);
		return (false);
	}
	*i += part_len;
	return (true);
}

static bool	add_quoted_word_part(t_word_part **current_part, char *input, int *i, t_word_part_type word_part_type)
{
	int		plain_part_len;
	char	*quoted_value;
	char	quote_char;

	(*i)++;
	if (word_part_type == SINGLE_QUOTED)
		quote_char = '\'';
	else
		quote_char = '"';
	plain_part_len = get_quoted_part_length(input, *i, quote_char);
	if (input[*i + plain_part_len] != quote_char)
		return (false);
	quoted_value = ft_substr(input, *i, plain_part_len);
	if (!quoted_value)
		return (false);
	if (!add_word_part_back(current_part, word_part_type, quoted_value))
		return (false);
	*i += plain_part_len + 1;
	return (true);
}
static bool	add_next_word_part(t_word_part **current_part, char *input, int *i)
{
	if (input[*i] == '\'')
		return (add_quoted_word_part(current_part, input, i, SINGLE_QUOTED));
	else if (input[*i] == '"')
		return (add_quoted_word_part(current_part, input, i, DOUBLE_QUOTED));
	else if (!is_space(input[*i]) && !is_operator(input[*i]))
		return (add_plain_word_part(current_part, input, i));
	return (false);
}

bool	add_word_parts(t_token *word_token, char *input, int *i)
{
	t_word_part	*head;
	t_word_part	**tail;

	head = NULL;
	tail = &word_token->word_parts;
	while (input[*i])
	{
		if (is_word_end(input[*i]))
			break;
		if (!add_next_word_part(tail, input, i))
			return (false);
		if (!head)
			head = *tail;
	}
	word_token->word_parts = head;
	return (true);
}
