/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:54:33 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/23 21:51:34 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	parse_one_redirect(t_token **current_token,
		t_redirect_node **redirects_head)
{
	t_redirect_node	*new_redirect;

	new_redirect = parse_redirect(current_token);
	if (!new_redirect)
		return (false);
	if (!*redirects_head)
		*redirects_head = new_redirect;
	else
		add_redirect_to_end(*redirects_head, new_redirect);
	return (true);
}

static t_command	*create_command(t_word *words, t_redirect_node *redirects)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->words = words;
	command->redirects = redirects;
	return (command);
}

static bool	parse_command_content(t_token **current_token, t_word **words_head,
		t_redirect_node **redirects_head)
{
	while ((*current_token)->type == TOKEN_WORD
		|| is_redirect((*current_token)->type))
	{
		if ((*current_token)->type == TOKEN_WORD)
		{
			if (!parse_one_word(current_token, words_head))
				return (false);
		}
		if (is_redirect((*current_token)->type))
		{
			if (!parse_one_redirect(current_token, redirects_head))
				return (false);
		}
	}
	return (true);
}

t_ast_node	*parse_command(t_token **current_token)
{
	t_ast_node		*command_node;
	t_command		*command;
	t_word			*words_head;
	t_redirect_node	*redirects_head;

	words_head = NULL;
	redirects_head = NULL;
	if (!parse_command_content(current_token, &words_head, &redirects_head))
		return (free_words(words_head), free_redirects(redirects_head), NULL);
	command_node = create_ast_node(NODE_COMMAND, NULL, NULL, NULL);
	if (!command_node)
		return (free_words(words_head), free_redirects(redirects_head), NULL);
	command = create_command(words_head, redirects_head);
	if (!command)
		return (free(command_node), free_words(words_head),
			free_redirects(redirects_head), NULL);
	command_node->command = command;
	return (command_node);
}
