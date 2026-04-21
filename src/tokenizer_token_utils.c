/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:13:10 by maxim             #+#    #+#             */
/*   Updated: 2026/04/21 14:18:29 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	add_token(t_token **current, t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	new_token->word_parts = NULL;
	if (*current)
		(*current)->next = new_token;
	*current = new_token;
	return (true);
}

bool	add_word_token(char *input, int *i, t_token **current)
{
	t_token	*word_token;

	if (!add_token(current, WORD, NULL))
		return (false);
	word_token = *current;
	if (!add_word_parts(word_token, input, i))
		return (false);
	return (true);
}

static int	get_operator_token_length(t_token_type token_type)
{
	if (token_type == OR || token_type == APPEND || token_type == HEREDOC || token_type == AND)
		return (2);
	else if (token_type != ERROR)
		return (1);
	return (0);
}

static t_token_type get_operator_token_type(char *input, int i)
{
	if (input[i] == '|' && input[i + 1] == '|')
		return (OR);
	else if (input[i] == '|')
		return (PIPE);
	else if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	else if (input[i] == '>')
		return (REDIRECT_OUT);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (HEREDOC);
	else if (input[i] == '<')
		return (REDIRECT_IN);
	else if (input[i] == '&' && input[i + 1] == '&')
		return (AND);
	else if (input[i] == '(')
		return (LEFT_PARENTHESIS);
	else if (input[i] == ')')
		return (RIGHT_PARENTHESIS);
	return (ERROR);
}

bool	add_operator_token(char *input, int *i, t_token **current)
{
	t_token_type	token_type;

	token_type = get_operator_token_type(input, *i);
	if (token_type == ERROR)
		return (false);
	*i += get_operator_token_length(token_type);
	return (add_token(current, token_type, NULL));
}
