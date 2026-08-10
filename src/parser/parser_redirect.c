/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 19:00:00 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/10 04:11:33 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_logical(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

bool	is_redirect(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static t_redirect_type	token_type_to_redirect_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	else if (type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	else if (type == TOKEN_APPEND)
		return (REDIRECT_APPEND);
	else if (type == TOKEN_HEREDOC)
		return (REDIRECT_HEREDOC);
	return (REDIRECT_IN);
}

void	add_redirect_to_end(t_redirect_node *head,
		t_redirect_node *new_redirect)
{
	t_redirect_node	*current;

	current = head;
	while (current->next)
		current = current->next;
	current->next = new_redirect;
}

t_redirect_node	*parse_redirect(t_token **current_token)
{
	t_redirect_node	*redirect_node;
	t_redirect_type	redirect_type;
	t_word			*target;

	redirect_node = malloc(sizeof(t_redirect_node));
	if (!redirect_node)
		return (NULL);
	redirect_type = token_type_to_redirect_type((*current_token)->type);
	*current_token = (*current_token)->next;
	if ((*current_token)->type != TOKEN_WORD)
		return (free(redirect_node), NULL);
	target = create_word_from_token(current_token);
	if (!target)
		return (free(redirect_node), NULL);
	redirect_node->type = redirect_type;
	redirect_node->target = target;
	redirect_node->next = NULL;
	redirect_node->target_str = NULL;
	*current_token = (*current_token)->next;
	return (redirect_node);
}
