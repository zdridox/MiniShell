/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:10:22 by maxim             #+#    #+#             */
/*   Updated: 2026/09/29 16:33:55 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_exec_status	collect_command_heredocs(t_redirect_node *redirects,
							t_shell *shell)
{
	t_cmd_io	heredoc_io;

	while (redirects)
	{
		if (redirects->type == REDIRECT_HEREDOC)
		{
			heredoc_io.input_fd = -1;
			heredoc_io.output_fd = STDOUT_FILENO;
			if (run_heredoc_in_child(redirects->target_str, &heredoc_io,
					shell) == EXEC_FAILURE)
				return (EXEC_FAILURE);
			redirects->heredoc_fd = heredoc_io.input_fd;
		}
		redirects = redirects->next;
	}
	return (EXEC_SUCCESS);
}

t_exec_status	collect_heredocs(t_ast_node *ast, t_shell *shell)
{
	if (ast == NULL)
		return (EXEC_SUCCESS);
	if (ast->type == NODE_COMMAND && ast->command != NULL
		&& collect_command_heredocs(ast->command->redirects,
			shell) == EXEC_FAILURE)
		return (EXEC_FAILURE);
	if (collect_heredocs(ast->left, shell) == EXEC_FAILURE)
		return (EXEC_FAILURE);
	return (collect_heredocs(ast->right, shell));
}
