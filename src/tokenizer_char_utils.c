/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_char_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:10:01 by maxim             #+#    #+#             */
/*   Updated: 2026/04/21 15:14:57 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_space(char c)
{
	return (('\t' < c && c < '\r') || c == ' ');
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')');
}

bool	is_word_end(char c)
{
	return (c == '\0' || is_space(c) || is_operator(c));
}
