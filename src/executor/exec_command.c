/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:59:48 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/02 21:01:40 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	init_cmd_io(t_cmd_io *cmd_io)
{
	cmd_io->input_fd = STDIN_FILENO;
	cmd_io->output_fd = STDOUT_FILENO;
}

t_exec_status	execute_command(t_command *command, t_shell *shell)
{
	t_cmd_io		cmd_io;
	t_our_command	*builtin_command;

	init_cmd_io(&cmd_io);
	if (command == NULL || command->argv == NULL || command->argv[0] == NULL)
		return (EXEC_FAILURE);
	if (handle_redirections(command->redirects, &cmd_io, shell) == ERROR)
		return (EXEC_FAILURE);
	builtin_command = find_builtin_command(command->argv[0], shell);
	if (builtin_command != NULL)
		return (execute_builtin_command(builtin_command, command->argv, &cmd_io,
				shell));
	else if (ft_strchr(command->argv[0], '/') != NULL)
		return (execute_binary_with_path(command->argv, &cmd_io, shell));
	else
		execute_linux_command(command->argv, &cmd_io, shell);
	return (EXEC_SUCCESS);
}
