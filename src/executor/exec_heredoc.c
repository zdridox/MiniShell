/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:15:51 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/03 21:00:05 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	run_heredoc_child_process(char *target_str, char *temp_file_path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!write_heredoc_to_file(target_str, temp_file_path))
		exit(1);
	exit(0);
}

static t_exec_status	finilize_heredoc(int status, char *temp_file_path,
							t_cmd_io *cmd_io)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(temp_file_path);
		free(temp_file_path);
		return (EXEC_FAILURE);
	}
	cmd_io->input_fd = open(temp_file_path, O_RDONLY);
	unlink(temp_file_path);
	free(temp_file_path);
	return (EXEC_SUCCESS);
}

t_exec_status	run_heredoc_in_child(char *target_str, t_cmd_io *cmd_io,
		t_shell *shell)
{
	char	*temp_file_path;
	pid_t	pid;
	int		status;

	temp_file_path = generate_temp_file_path(shell);
	if (!temp_file_path)
	{
		display_error_message("Failed to create temporary file for heredoc");
		return (EXEC_FAILURE);
	}
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
		run_heredoc_child_process(target_str, temp_file_path);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
	return (finilize_heredoc(status, temp_file_path, cmd_io));
}
