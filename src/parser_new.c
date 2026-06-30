/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:47:02 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/06/30 19:11:50 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_new.h"

t_ast_node	*parse_logical(t_token **current_token);

bool	is_redirect(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

bool	is_logical(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

t_redirect_type	token_type_to_redirect_type(t_token_type type)
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

t_word	*create_word_from_token(t_token **token)
{
	t_word		*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->next = NULL;
	// parer takes ownership of word_parts, so token should not free them
	word->word_parts = (*token)->word_parts;
	(*token)->word_parts = NULL;
	return (word);
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
	*current_token = (*current_token)->next;
	return (redirect_node);
}

t_ast_node	*create_ast_node(t_node_type type, t_command *command, t_ast_node *left, t_ast_node *right)
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

void	add_word_to_end(t_word *head, t_word *new_word)
{
	t_word	*current;

	current = head;
	while (current->next)
		current = current->next;
	current->next = new_word;
}

bool	parse_one_word(t_token **current_token, t_word **words_head)
{
	t_word	*new_word;

	new_word = create_word_from_token(current_token);
	if (!new_word)
		return (false);
	if (!*words_head)
		*words_head = new_word;
	else
		add_word_to_end(*words_head, new_word);
	(*current_token) = (*current_token)->next;
	return (true);
}

void	add_redirect_to_end(t_redirect_node *head, t_redirect_node *new_redirect)
{
	t_redirect_node	*current;

	current = head;
	while (current->next)
		current = current->next;
	current->next = new_redirect;
}

bool	parse_one_redirect(t_token **current_token, t_redirect_node **redirects_head)
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

void	free_words(t_word *words)
{
	t_word	*temp;

	while (words)
	{
		free_word_parts(words->word_parts);
		temp = words;
		words = words->next;
		free(temp);
	}
}

void	free_redirects(t_redirect_node *redirects)
{
	t_redirect_node	*temp;

	while (redirects)
	{
		free_words(redirects->target);
		temp = redirects;
		redirects = redirects->next;
		free(temp);
	}
}

t_command	*create_command(t_word *words, t_redirect_node *redirects)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->words = words;
	command->redirects = redirects;
	return (command);
}

t_ast_node	*parse_command(t_token **current_token)
{
	t_ast_node		*command_node;
	t_command		*command;
	t_word			*words_head;
	t_redirect_node	*redirects_head;

	words_head = NULL;
	redirects_head = NULL;
	while ((*current_token)->type == TOKEN_WORD || is_redirect((*current_token)->type))
	{
		if ((*current_token)->type == TOKEN_WORD)
		{
			if (!parse_one_word(current_token, &words_head))
				return (free_words(words_head), free_redirects(redirects_head), NULL);
		}
		if (is_redirect((*current_token)->type))
		{
			if (!parse_one_redirect(current_token, &redirects_head))
				return (free_words(words_head), free_redirects(redirects_head), NULL);
		}
	}
	command_node = create_ast_node(NODE_COMMAND, NULL, NULL, NULL);
	if (!command_node)
		return (free_words(words_head), free_redirects(redirects_head), NULL);
	command = create_command(words_head, redirects_head);
	if (!command)
		return (free(command_node), free_words(words_head), free_redirects(redirects_head), NULL);
	command_node->command = command;
	return (command_node);
}
//argv is dynanic sthring
void	free_argv(char **argv)
{
	free(argv[0]);
	free(argv);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->command)
	{
		free_words(node->command->words);
		free_redirects(node->command->redirects);
		free_argv(node->command->argv);
		free(node->command);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

t_ast_node	*parse_in_parentheses(t_token **current_token)
{
	t_ast_node	*group_node;

	(*current_token) = (*current_token)->next; // skip LPAREN
	group_node = parse_logical(current_token);
	if (!group_node)
		return (NULL);
	if (!*current_token || (*current_token)->type != TOKEN_RIGHT_PARENTHESIS)
		return (free_ast(group_node), NULL);
	(*current_token) = (*current_token)->next; // skip RPAREN
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
	else if (*current_token && ((*current_token)->type == TOKEN_WORD || is_redirect((*current_token)->type)))
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
