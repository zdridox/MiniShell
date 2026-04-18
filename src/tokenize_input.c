/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:45:05 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/04/18 22:59:06 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

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

bool	add_token(t_token **current, t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	if (*current)
		(*current)->next = new_token;
	*current = new_token;
	return (true);
}

void	add_operator_token(char *input, int *i, t_token **current)
{
	if (input[*i] == '|' && input[*i + 1] == '|')
		add_token(current, AND, NULL);
	else if (input[*i] == '|')
		add_token(current, PIPE, NULL);
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(current, APPEND, NULL);
		(*i)++;
	}
	else if (input[*i] == '>')
		add_token(current, REDIRECT_OUT, NULL);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(current, HEREDOC, NULL);
		(*i)++;
	}
	else if (input[*i] == '<')
		add_token(current, REDIRECT_IN, NULL);
	else if (input[*i] == '&' && input[*i + 1] == '&')
		add_token(current, AND, NULL);
	else if (input[*i] == '(')
		add_token(current, LEFT_PARENTHESIS, NULL);
	else if (input[*i] == ')')
		add_token(current, RIGHT_PARENTHESIS, NULL);
	(*i)++;
}

int	calculate_word_length(char *input)
{
	int		len;
	bool	in_quote;

	len = 0;
	in_quote = false;
	while (input[len] && (in_quote || (!is_space(input[len]) && !is_operator(input[len]))))
	{
		if (is_quote(input[len]))
			in_quote = !in_quote;
		len++;
	}
	return (len);
}

bool	add_word_token(char *input, int *i, t_token **current)
{
	int		len;
	char	*word;

	len = calculate_word_length(input + *i);
	word = malloc(len + 1);
	if (!word)
		return (false);
	ft_memcpy(word, input + *i, len);
	word[len] = '\0';
	*i += len;
	if (!add_token(current, WORD, word))
	{
		free(word);
		return (false);
	}
	return (true);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	t_token	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (is_operator(input[i]))
			add_operator_token(input, &i, &current);
		else
			add_word_token(input, &i, &current);
		if (!head)
			head = current;
	}
	add_token(&current, END, NULL);
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

int	main(int argc, char **argv)
{
	char	*input;
	t_token	*tokens;
	t_token *current;
	char	*token_values[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", "APPEND", "HEREDOC", "AND", "OR", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "ERROR", "END"};
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
		printf("Token %d: Type=%s, Value=%s\n", i , token_values[current->type], current->value ? current->value : "NULL");
		current = current->next;
		i++;
	}
	free_tokens(tokens);
	return (0);
}
