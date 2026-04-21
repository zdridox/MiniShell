/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word_length.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:30:17 by maxim             #+#    #+#             */
/*   Updated: 2026/04/21 14:39:59 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	get_plain_part_length(char *input, int i)
{
	int		len;

	len = 0;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]) && !is_quote(input[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	get_quoted_part_length(char *input, int i, char quote_char)
{
	int	len;

	len = 0;
	while (input[i] && input[i] != quote_char)
	{
		len++;
		i++;
	}
	return (len);
}

