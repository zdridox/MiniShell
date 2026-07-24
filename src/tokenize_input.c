/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:45:05 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/24 16:38:23 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	add_next_token(char *input, int *i, t_token **current)
{
	if (is_operator(input[*i]))
	{
		if (!add_operator_token(input, i, current))
			return (false);
	}
	else
	{
		if (!add_word_token(input, i, current))
			return (false);
	}
	return (true);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	t_token	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (!add_next_token(input, &i, &tail))
		{
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = tail;
	}
	add_token(&tail, TOKEN_END);
	return (head);
}
