/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:48:50 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/29 16:01:06 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*expand_redirect_target_str(t_word *redirect_word, t_shell *shell)
{
	char	**expanded_argv;
	char	*expanded_str;

	expanded_argv = expand_to_argv(redirect_word, shell);
	if (!expanded_argv)
		return (NULL);
	if (str_arr_len(expanded_argv) != 1)
	{
		display_error_message("Ambiguous redirect");
		free_argv(expanded_argv);
		return (NULL);
	}
	expanded_str = ft_strdup(expanded_argv[0]);
	free_argv(expanded_argv);
	return (expanded_str);
}

static bool	expand_words_in_redirects(
	t_redirect_node *redirects, t_shell *shell)
{
	while (redirects)
	{
		redirects->target_str = expand_redirect_target_str(
				redirects->target, shell);
		if (!redirects->target_str)
			return (false);
		redirects = redirects->next;
	}
	return (true);
}

bool	expand_words_in_ast(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (true);
	if (node->type == NODE_COMMAND)
	{
		node->command->argv = expand_to_argv(node->command->words, shell);
		if (!node->command->argv)
			return (false);
		if (!expand_words_in_redirects(node->command->redirects, shell))
			return (false);
	}
	if (!expand_words_in_ast(node->left, shell))
		return (false);
	if (!expand_words_in_ast(node->right, shell))
		return (false);
	return (true);
}
