/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:26 by maxim             #+#    #+#             */
/*   Updated: 2026/07/04 19:35:54 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_word_parts(t_word_part *word_parts)
{
	t_word_part	*temp;

	while (word_parts)
	{
		temp = word_parts;
		word_parts = word_parts->next;
		free(temp);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->word_parts)
			free_word_parts(temp->word_parts);
		free(temp);
	}
}
