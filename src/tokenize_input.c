/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:45:05 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/04/21 14:42:57 by maxim            ###   ########.fr       */
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
			break;
		if (!add_next_token(input, &i, &tail))
		{
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = tail;
	}
	add_token(&tail, END, NULL);
	return (head);
}

int	main(int argc, char **argv)
{
	char	*input;
	t_token	*tokens;
	t_token *current;
	char	*token_values[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", "APPEND", "HEREDOC", "AND", "OR", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "ERROR", "END"};
	char	*word_part_values[] = {"PLAIN", "SINGLE_QUOTED", "DOUBLE_QUOTED"};
	int		i;

	if (argc != 2)
	{
		printf("Usage: %s <input>\n", argv[0]);
		return (1);
	}
	input = argv[1];
	tokens = tokenize_input(input);
	i = 1;
	current = tokens;
	while (current)
	{
		printf("Token %d: Type=%s, Value=\'%s\'\n", i , token_values[current->type], current->value ? current->value : "NULL");
		if (current->type == WORD)
		{
			t_word_part *part = current->word_parts;
			int part_num = 1;
			while (part)
			{
				printf("	Word Part %d: Type=%s, Value=\'%s\'\n", part_num, word_part_values[part->type], part->value ? part->value : "NULL");
				part = part->next;
				part_num++;
			}
		}
		current = current->next;
		i++;
	}
	free_tokens(tokens);
	return (0);
}
