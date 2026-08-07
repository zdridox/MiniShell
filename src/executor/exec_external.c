/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:01:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/07 10:41:28 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	**get_list_of_paths(t_shell *shell)
{
	char	**list_of_paths;
	char	*path;

	path = get_env_value("PATH", shell->env);
	if (path == NULL)
		return (NULL);
	list_of_paths = ft_split(path, ':');
	return (list_of_paths);
}

static char	*find_bin_path(char *bin_name, t_shell *shell)
{
	char	**list_of_paths;
	char	*bin_path;
	int		i;

	if (bin_name == NULL || bin_name[0] == '\0')
		return (NULL);
	list_of_paths = get_list_of_paths(shell);
	if (list_of_paths == NULL)
		error_exit("Memory allocation failed", shell);
	i = 0;
	while (list_of_paths[i])
	{
		bin_path = ft_strjoin_three(list_of_paths[i], "/", bin_name);
		if (bin_path == NULL)
			error_exit("Memory allocation failed", shell);
		if (access(bin_path, X_OK) == 0)
		{
			free_str_arr(list_of_paths);
			return (bin_path);
		}
		free(bin_path);
		i++;
	}
	free_str_arr(list_of_paths);
	return (NULL);
}

static void	run_binary_in_child(char *bin_path, char **argv,
				t_cmd_io *cmd_io, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	change_stream_fd(cmd_io->input_fd, STDIN_FILENO);
	change_stream_fd(cmd_io->output_fd, STDOUT_FILENO);
	execve(bin_path, argv, shell->env);
	if (access(bin_path, F_OK) != 0)
	{
		display_error_message_with_context("No such file or directory: ",
			argv[0]);
		exit(127);
	}
	if (access(bin_path, X_OK) != 0)
	{
		display_error_message_with_context("Permission denied: ", argv[0]);
		exit(126);
	}
	if (is_directory(bin_path))
	{
		display_error_message_with_context("Is a directory: ", argv[0]);
		exit(126);
	}
	error_exit("Failed to execute binary", shell);
}

t_exec_status	execute_binary_with_path(char **argv, t_cmd_io *cmd_io,
		t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		display_error_message("Failed to create process");
		return (EXEC_FAILURE);
	}
	else if (pid == CHILD_PROCESS)
		run_binary_in_child(argv[0], argv, cmd_io, shell);
	signal(SIGINT, SIG_IGN);
	close_fds(cmd_io->input_fd, cmd_io->output_fd);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
	return (EXEC_SUCCESS);
}

void	execute_linux_command(char **argv, t_cmd_io *cmd_io, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*bin_path;

	bin_path = find_bin_path(argv[0], shell);
	if (bin_path == NULL)
	{
		display_error_message_with_context("Command not found: ", argv[0]);
		update_exit_status(shell, 127);
		return ;
	}
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
		run_binary_in_child(bin_path, argv, cmd_io, shell);
	signal(SIGINT, SIG_IGN);
	close_fds(cmd_io->input_fd, cmd_io->output_fd);
	free(bin_path);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
}
