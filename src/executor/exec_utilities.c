/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:21:25 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/03 18:23:47 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	update_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
	{
		shell->last_exit_code = WEXITSTATUS(status);
		return ;
	}
	if (WIFSIGNALED(status))
	{
		shell->last_exit_code = 128 + WTERMSIG(status);
		return ;
	}
	else
	{
		shell->last_exit_code = status;
		return ;
	}
}

t_our_command	*find_builtin_command(char *command_name, t_shell *shell)
{
	t_our_command	*our_commands;

	if (command_name == NULL || shell == NULL)
		return (NULL);
	our_commands = shell->our_commands;
	while (our_commands && our_commands->name)
	{
		if (ft_strcmp(command_name, our_commands->name) == EQUAL)
			return (our_commands);
		our_commands++;
	}
	return (NULL);
}

void	change_stream_fd(int fd, int stream_fd)
{
	if (fd != stream_fd)
	{
		dup2(fd, stream_fd);
		close(fd);
	}
}

void	close_fds(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO && input_fd != STDOUT_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO && output_fd != STDIN_FILENO)
		close(output_fd);
}
