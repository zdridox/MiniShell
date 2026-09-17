/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:50:35 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/03 21:25:45 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_exec_status	execute_logical_and(t_ast_node *ast, t_shell *shell)
{
	t_exec_status	execution_status;

	execution_status = execute_node(ast->left, shell);
	if (execution_status != EXEC_SUCCESS)
		return (execution_status);
	if (shell->last_exit_code == 0)
		return (execute_node(ast->right, shell));
	else
		return (EXEC_SUCCESS);
}

static t_exec_status	execute_logical_or(t_ast_node *ast, t_shell *shell)
{
	t_exec_status	execution_status;

	execution_status = execute_node(ast->left, shell);
	if (execution_status != EXEC_SUCCESS)
		return (execution_status);
	if (shell->last_exit_code != 0)
		return (execute_node(ast->right, shell));
	else
		return (EXEC_SUCCESS);
}

t_exec_status	execute_node(t_ast_node *ast, t_shell *shell)
{
	t_exec_status	execution_status;

	if (ast->type == NODE_COMMAND)
		execution_status = execute_command(ast->command, shell);
	else if (ast->type == NODE_PIPE)
		execution_status = execute_pipe(ast, shell);
	else if (ast->type == NODE_AND)
		execution_status = execute_logical_and(ast, shell);
	else if (ast->type == NODE_OR)
		execution_status = execute_logical_or(ast, shell);
	else
		execution_status = EXEC_FAILURE;
	return (execution_status);
}

void	execute_parsed(t_ast_node *ast, t_shell *shell)
{
	if (ast == NULL || shell == NULL)
		return ;
	execute_node(ast, shell);
}
