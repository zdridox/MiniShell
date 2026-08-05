/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:28:58 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/23 21:49:19 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//argv is dynanic sthring
void	free_argv(char **argv)
{
	free(argv[0]);
	free(argv);
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
