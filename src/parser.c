/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:47:02 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/23 21:48:53 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_logical(t_token **current_token);

t_ast_node	*parse_in_parentheses(t_token **current_token)
{
	t_ast_node	*group_node;

	(*current_token) = (*current_token)->next;
	group_node = parse_logical(current_token);
	if (!group_node)
		return (NULL);
	if (!*current_token || (*current_token)->type != TOKEN_RIGHT_PARENTHESIS)
		return (free_ast(group_node), NULL);
	(*current_token) = (*current_token)->next;
	return (group_node);
}

t_ast_node	*parse_primary(t_token **current_token)
{
	t_ast_node	*group_node;
	t_ast_node	*command_node;

	if (*current_token && (*current_token)->type == TOKEN_LEFT_PARENTHESIS)
	{
		group_node = parse_in_parentheses(current_token);
		if (!group_node)
			return (NULL);
		return (group_node);
	}
	else if (*current_token && ((*current_token)->type == TOKEN_WORD
			|| is_redirect((*current_token)->type)))
	{
		command_node = parse_command(current_token);
		if (!command_node)
			return (NULL);
		return (command_node);
	}
	else
		return (NULL);
}

t_ast_node	*parse_pipeline(t_token **current_token)
{
	t_ast_node	*pipeline_node;
	t_ast_node	*left;
	t_ast_node	*right;

	pipeline_node = NULL;
	left = parse_primary(current_token);
	if (!left)
		return (NULL);
	pipeline_node = left;
	while (*current_token && (*current_token)->type == TOKEN_PIPE)
	{
		(*current_token) = (*current_token)->next;
		right = parse_primary(current_token);
		if (!right)
			return (free_ast(left), NULL);
		pipeline_node = create_ast_node(NODE_PIPE, NULL, left, right);
		if (!pipeline_node)
			return (free_ast(left), free_ast(right), NULL);
		left = pipeline_node;
	}
	if (!pipeline_node)
		return (left);
	else
		return (pipeline_node);
}

t_ast_node	*parse_logical(t_token **current_token)
{
	t_ast_node	*logical_node;
	t_ast_node	*left;
	t_ast_node	*right;
	t_node_type	logical_node_type;

	logical_node = NULL;
	left = parse_pipeline(current_token);
	if (!left)
		return (NULL);
	while (*current_token && is_logical((*current_token)->type))
	{
		logical_node_type = token_type_to_node_type((*current_token)->type);
		(*current_token) = (*current_token)->next;
		right = parse_pipeline(current_token);
		if (!right)
			return (free_ast(left), NULL);
		logical_node = create_ast_node(logical_node_type, NULL, left, right);
		if (!logical_node)
			return (free_ast(left), free_ast(right), NULL);
		left = logical_node;
	}
	if (!logical_node)
		return (left);
	else
		return (logical_node);
}

t_ast_node	*parse_tokens(t_token *tokens)
{
	t_ast_node	*root;

	root = parse_logical(&tokens);
	return (root);
}
