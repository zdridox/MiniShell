/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:42:19 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/23 21:49:46 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node_type	token_type_to_node_type(t_token_type type)
{
	if (type == TOKEN_AND)
		return (NODE_AND);
	else if (type == TOKEN_OR)
		return (NODE_OR);
	else if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	else
		return (NODE_COMMAND);
}

t_ast_node	*create_ast_node(t_node_type type, t_command *command,
		t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->command = command;
	node->left = left;
	node->right = right;
	return (node);
}
