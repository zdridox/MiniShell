/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/07/16 18:01:42 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_bin_path(char *bin_name, t_shell *shell)
{
	char	**paths;
	char	*path;
	char	*bin_path;
	int		i;

	if (bin_name == NULL || bin_name[0] == '\0')
		return (NULL);
	path = get_env_value("PATH", shell->env);
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		error_exit("Memory allocation failed", shell);
	i = 0;
	while (paths[i])
	{
		bin_path = ft_strjoin_three(paths[i], "/", bin_name);
		if (bin_path == NULL)
			error_exit("Memory allocation failed", shell);
		if (access(bin_path, X_OK) == 0)
		{
			free_str_arr(paths);
			return (bin_path);
		}
		free(bin_path);
		i++;
	}
	free_str_arr(paths);
	return (NULL);
}

int	is_builtin_command(char *command_name, t_our_command *command)
{
	while (command && command->name)
	{
		if (ft_strcmp(command_name, command->name) == EQUAL)
			return (true);
		command++;
	}
	return (false);
}

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
	if (input_fd != STDIN && input_fd != STDOUT)
		close(input_fd);
	if (output_fd != STDOUT && output_fd != STDIN)
		close(output_fd);
}

t_exec_status	execute_our_command_in_child(t_our_command_fn function, char **argv, t_cmd_io *cmd_io, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		change_stream_fd(cmd_io->input_fd, STDIN);
		change_stream_fd(cmd_io->output_fd, STDOUT);
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

// my version of OOP:
t_exec_status	execute_builtin_command(t_our_command *our_command, char **argv, t_cmd_io *cmd_io, t_shell *shell)
{
	if (our_command->run_in_child_process)
		return (execute_our_command_in_child(our_command->function, argv, cmd_io, shell));
	shell->last_exit_code = our_command->function(shell, argv);
	return (EXEC_SUCCESS);
}

t_exec_status	execute_binary_with_path(char **argv, t_cmd_io *cmd_io, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		display_error_message("Failed to create process");
		return (EXEC_FAILURE);
	}
	else if (pid == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		change_stream_fd(cmd_io->input_fd, STDIN);
		change_stream_fd(cmd_io->output_fd, STDOUT);
		execve(argv[0], argv, shell->env);
		display_error_message("Command execution failed");
		return (EXEC_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	close_fds(cmd_io->input_fd, cmd_io->output_fd);
	signal(SIGINT, sigint_handler);
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
		// display_error_message("Command not found");
		printf("minishell: command not found: %s\n", argv[0]);
		return ;
	}
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		change_stream_fd(cmd_io->input_fd, STDIN);
		change_stream_fd(cmd_io->output_fd, STDOUT);
		execve(bin_path, argv, shell->env);
		error_exit("Command execution failed", shell);
	}
	signal(SIGINT, SIG_IGN);
	close_fds(cmd_io->input_fd, cmd_io->output_fd);
	free(bin_path);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
}

t_exec_status	run_heredoc_in_child(char *target_str, t_cmd_io *cmd_io, t_shell *shell)
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
	{
		signal(SIGINT, SIG_DFL);
		if (!write_heredoc_to_file(target_str, temp_file_path))
			exit(1);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
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

int	handle_redirections(t_redirect_node *redirects, t_cmd_io *cmd_io, t_shell *shell)
{
	while (redirects != NULL)
	{
		if (redirects->type == REDIRECT_IN)
		{
			if (cmd_io->input_fd != STDIN)
				close(cmd_io->input_fd);
			cmd_io->input_fd = open(redirects->target_str, O_RDONLY);
			if (cmd_io->input_fd < 0)
			{
				cmd_io->input_fd = STDIN;
				close_fds(cmd_io->input_fd, cmd_io->output_fd);
				display_error_message("Failed to open input file");
				return (ERROR);
			}
		}
		else if (redirects->type == REDIRECT_OUT)
		{
			if (cmd_io->output_fd != STDOUT)
				close(cmd_io->output_fd);
			cmd_io->output_fd = open(redirects->target_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd_io->output_fd < 0)
			{
				cmd_io->output_fd = STDOUT;
				close_fds(cmd_io->input_fd, cmd_io->output_fd);
				display_error_message("Failed to open output file");
				return (ERROR);
			}
		}
		else if (redirects->type == REDIRECT_APPEND)
		{
			if (cmd_io->output_fd != STDOUT)
				close(cmd_io->output_fd);
			cmd_io->output_fd = open(redirects->target_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd_io->output_fd < 0)
			{
				cmd_io->output_fd = STDOUT;
				close_fds(cmd_io->input_fd, cmd_io->output_fd);
				display_error_message("Failed to open output file");
				return (ERROR);
			}
		}
		else if (redirects->type == REDIRECT_HEREDOC)
		{
			if (cmd_io->input_fd != STDIN)
				close(cmd_io->input_fd);
			if (run_heredoc_in_child(redirects->target_str, cmd_io, shell) == EXEC_FAILURE)
			{
				cmd_io->input_fd = STDIN;
				close_fds(cmd_io->input_fd, cmd_io->output_fd);
				return (ERROR);
			}
		}
		redirects = redirects->next;
	}
	return (SUCCESS);
}

void	init_cmd_io(t_cmd_io *cmd_io)
{
	cmd_io->input_fd = STDIN;
	cmd_io->output_fd = STDOUT;
}

t_exec_status	execute_command(t_command *command, t_shell *shell)
{
	t_cmd_io			cmd_io;
	t_our_command		*builtin_command;

	init_cmd_io(&cmd_io);
	if (command == NULL || command->argv == NULL || command->argv[0] == NULL)
		return (EXEC_FAILURE);
	if (handle_redirections(command->redirects, &cmd_io, shell) == ERROR)
		return (EXEC_FAILURE);
	builtin_command = find_builtin_command(command->argv[0], shell);
	if (builtin_command != NULL)
		return (execute_builtin_command(builtin_command, command->argv, &cmd_io, shell));
	else if (ft_strchr(command->argv[0], '/') != NULL)
		return(execute_binary_with_path(command->argv, &cmd_io, shell));
	else
		execute_linux_command(command->argv, &cmd_io, shell);
	return (EXEC_SUCCESS);
}

t_exec_status	execute_node(t_ast_node *ast, t_shell *shell);

t_exec_status	execute_pipe(t_ast_node *ast, t_shell *shell)
{
	int	pipe_fds[2];
	int	pid_left;
	int	pid_right;
	int	status;

	if (pipe(pipe_fds) < 0)
	{
		display_error_message("Failed to create pipe");
		return (EXEC_FAILURE);
	}
	pid_left = fork();
	if (pid_left < 0)
	{
		display_error_message("Failed to create process");
		return (EXEC_FAILURE);
	}
	if (pid_left == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		dup2(pipe_fds[1], STDOUT);
		close_fds(pipe_fds[0], pipe_fds[1]);
		execute_node(ast->left, shell);
		exit(shell->last_exit_code);
	}
	signal(SIGINT, SIG_IGN);
	pid_right = fork();
	if (pid_right < 0)
	{
		display_error_message("Failed to create process");
		return (EXEC_FAILURE);
	}
	if (pid_right == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		dup2(pipe_fds[0], STDIN);
		close_fds(pipe_fds[0], pipe_fds[1]);
		execute_node(ast->right, shell);
		exit(shell->last_exit_code);
	}
	close_fds(pipe_fds[0], pipe_fds[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	signal(SIGINT, sigint_handler);
	update_exit_status(shell, status);
	return (EXEC_SUCCESS);
}

t_exec_status	execute_logical_and(t_ast_node *ast, t_shell *shell)
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

t_exec_status	execute_logical_or(t_ast_node *ast, t_shell *shell)
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
		execution_status  = execute_logical_or(ast, shell);
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
