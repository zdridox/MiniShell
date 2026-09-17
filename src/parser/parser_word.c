/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:44:34 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/23 21:51:25 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_word	*create_word_from_token(t_token **token)
{
	t_word		*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->next = NULL;
	word->word_parts = (*token)->word_parts;
	(*token)->word_parts = NULL;
	return (word);
}

static void	add_word_to_end(t_word *head, t_word *new_word)
{
	t_word	*current;

	current = head;
	while (current->next)
		current = current->next;
	current->next = new_word;
}

bool	parse_one_word(t_token **current_token, t_word **words_head)
{
	t_word	*new_word;

	new_word = create_word_from_token(current_token);
	if (!new_word)
		return (false);
	if (!*words_head)
		*words_head = new_word;
	else
		add_word_to_end(*words_head, new_word);
	(*current_token) = (*current_token)->next;
	return (true);
}
