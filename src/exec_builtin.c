/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 21:04:18 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/04 22:27:54 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_exec_status	execute_our_command_in_child(t_our_command_fn function,
		char **argv, t_cmd_io *cmd_io, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		change_stream_fd(cmd_io->input_fd, STDIN_FILENO);
		change_stream_fd(cmd_io->output_fd, STDOUT_FILENO);
		status = function(shell, argv);
		exit(status);
	}
	signal(SIGINT, SIG_IGN);
	close_fds(cmd_io->input_fd, cmd_io->output_fd);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
	return (EXEC_SUCCESS);
}

t_exec_status	execute_builtin_command(t_our_command *our_command, char **argv,
		t_cmd_io *cmd_io, t_shell *shell)
{
	if (our_command->run_in_child_process)
		return (execute_our_command_in_child(our_command->function, argv,
				cmd_io, shell));
	shell->last_exit_code = our_command->function(shell, argv);
	return (EXEC_SUCCESS);
}
