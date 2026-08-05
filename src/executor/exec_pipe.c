/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:11:21 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/04 22:18:44 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	run_pipe_child(t_ast_node *ast_node, t_shell *shell,
				int *pipe_fds, bool is_left)
{
	signal(SIGINT, SIG_DFL);
	if (is_left)
		dup2(pipe_fds[1], STDOUT_FILENO);
	else
		dup2(pipe_fds[0], STDIN_FILENO);
	close_fds(pipe_fds[0], pipe_fds[1]);
	execute_node(ast_node, shell);
	exit(shell->last_exit_code);
}

static t_exec_status	wait_for_child_processes(int pid_left, int pid_right,
							t_shell *shell)
{
	int	status;

	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
	return (EXEC_SUCCESS);
}

t_exec_status	execute_pipe(t_ast_node *ast, t_shell *shell)
{
	int	pipe_fds[2];
	int	pid_left;
	int	pid_right;

	if (pipe(pipe_fds) < 0)
		return (display_error_message("Failed to create pipe"), EXEC_FAILURE);
	pid_left = fork();
	if (pid_left < 0)
		return (display_error_message("Failed to create process"),
			EXEC_FAILURE);
	if (pid_left == CHILD_PROCESS)
		run_pipe_child(ast->left, shell, pipe_fds, true);
	signal(SIGINT, SIG_IGN);
	pid_right = fork();
	if (pid_right < 0)
		return (display_error_message("Failed to create process"),
			EXEC_FAILURE);
	if (pid_right == CHILD_PROCESS)
		run_pipe_child(ast->right, shell, pipe_fds, false);
	close_fds(pipe_fds[0], pipe_fds[1]);
	return (wait_for_child_processes(pid_left, pid_right, shell));
}
