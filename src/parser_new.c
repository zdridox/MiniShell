/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:47:02 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/04/22 21:08:04 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_new.h"

bool	is_redirect(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC);
}

t_redirect_type	token_type_to_redirect_type(t_token_type type)
{
	if (type == REDIRECT_IN)
		return (REDIRECT_IN);
	else if (type == REDIRECT_OUT)
		return (REDIRECT_OUT);
	else if (type == APPEND)
		return (REDIRECT_APPEND);
	else if (type == HEREDOC)
		return (REDIRECT_HEREDOC);
}

t_word	*create_word_from_token(t_token *token)
{
	t_word		*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->next = NULL;
	// parer takes ownership of word_parts, so token should not free them
	word->word_parts = token->word_parts;
	return (word);
}

t_redirect_node	*parse_redirect(t_token **current_token)
{
	t_redirect_node	*redirect_node;
	t_token_type	redirect_type;
	t_word			*target;

	redirect_node = malloc(sizeof(t_redirect_node));
	if (!redirect_node)
		return (NULL);
	*current_token = (*current_token)->next;
	if ((*current_token)->type != WORD)
		return (free(redirect_node), NULL);
	target = create_word_from_token(*current_token);
	if (!target)
		return (free(redirect_node), NULL);
	redirect_type = token_type_to_redirect_type((*current_token)->type);
	redirect_node->type = redirect_type;
	redirect_node->target = target;
	redirect_node->next = NULL;
	*current_token = (*current_token)->next;
	return (redirect_node);
}

t_ast_node	*parse_tokens(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;


}
