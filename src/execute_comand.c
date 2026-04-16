/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/04/16 19:10:35 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_bin_path(char *bin_name, t_shell *shell)
{
	char	**paths;
	char	*path;
	char	*bin_path;
	int		i;

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

int	is_builtin_command(char *command_name, t_our_commands *command)
{
	while (command && command->name)
	{
		if (ft_strcmp(command_name, command->name) == EQUAL)
			return (TRUE);
		command++;
	}
	return (FALSE);
}

void	close_all_fds(t_cmd_node *cmds)
{
	t_cmd_node	*current_cmd;

	current_cmd = cmds;
	while (current_cmd)
	{
		if (current_cmd->input_fd != STDIN)
			close(current_cmd->input_fd);
		if (current_cmd->output_fd != STDOUT)
			close(current_cmd->output_fd);
		current_cmd = current_cmd->next;
	}
}

void	execute_linux_command(char **tokens, t_shell *shell, int input_fd, int output_fd, pid_t *pid)
{
	char	*bin_path;

	bin_path = find_bin_path(tokens[0], shell);
	if (bin_path == NULL)
	{
		// display_error_message("Command not found");
		printf("minishell: command not found: %s\n", tokens[0]);
		return ;
	}
	*pid = fork();
	if (*pid < 0)
		error_exit("Can make new process", shell);
	else if (*pid == CHILD_PROCESS)
	{
		if (input_fd != STDIN)
		{
			dup2(input_fd, STDIN);
			close(input_fd);
		}
		if (output_fd != STDOUT)
		{
			dup2(output_fd, STDOUT);
			close(output_fd);
		}
		execve(bin_path, tokens, shell->env);
		error_exit("Command execution failed", shell);
	}
	/*
	if (input_fd != STDIN)
		close(input_fd);
	if (output_fd != STDOUT)
		close(output_fd);
	*/
	free(bin_path);
}

void	execute_builtin_command(char **tokens, t_shell *shell)
{
	t_our_commands	*command;

	command = shell->our_commands;
	while (command && command->name)
	{
		if (ft_strcmp(tokens[0], command->name) == EQUAL)
		{
			command->function(shell, tokens);
			return ;
		}
		command++;
	}
}

void	execute_binary_with_path(char **tokens, t_shell *shell, int input_fd, int output_fd, pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		error_exit("Can make new process", shell);
	else if (*pid == CHILD_PROCESS)
	{
		if (input_fd != STDIN)
		{
			dup2(input_fd, STDIN);
			close(input_fd);
		}
		if (output_fd != STDOUT)
		{
			dup2(output_fd, STDOUT);
			close(output_fd);
		}
		execve(tokens[0], tokens, shell->env);
		error_exit("Command execution failed", shell);
	}
	/*
	if (input_fd != STDIN)
		close(input_fd);
	if (output_fd != STDOUT)
		close(output_fd);
	*/
}
/*
void	execute_comand(char **tokens, t_shell *shell)
{
	if (tokens[0] == NULL)
		return ;
	if (is_builtin_command(tokens[0], shell->our_commands) == TRUE)
		execute_builtin_command(tokens, shell);
	else if (ft_strchr(tokens[0], '/') != NULL)
		execute_binary_with_path(tokens, shell);
	else
		execute_linux_command(tokens, shell);
}
*/

int	prepare_command_redirections(t_cmd_node *cmds, int *input_fd, int *output_fd)
{
	t_flag_node	*current_flag;

	current_flag = cmds->flags;
	if (current_flag == NULL)
		return (SUCCESS);
	while (current_flag != NULL)
	{
		if (current_flag->flag == READ_FROM_FILE)
		{
			if (*input_fd != STDIN)
				close(*input_fd);
			*input_fd = open(current_flag->flag_arg, O_RDONLY);
			if (*input_fd < 0)
			{
				close_all_fds(cmds);
				display_error_message("Failed to open input file");
				return (ERROR);
			}
		}
		if (current_flag->flag == OVERWRITE)
		{
			if (*output_fd != STDOUT)
				close(*output_fd);
			*output_fd = open(current_flag->flag_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*output_fd < 0)
			{
				close_all_fds(cmds);
				display_error_message("Failed to open output file");
				return (ERROR);
			}
		}
		if (current_flag->flag == APPEND)
		{
			if (*output_fd != STDOUT)
				close(*output_fd);
			*output_fd = open(current_flag->flag_arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*output_fd < 0)
			{
				close_all_fds(cmds);
				display_error_message("Failed to open output file");
				return (ERROR);
			}
		}
		current_flag = current_flag->next;
	}
	return (SUCCESS);
}

int	prepare_pipe_redirections(t_cmd_node *cmds)
{
	int	pipe_fds[2];
	t_cmd_node	*current_cmd;
	t_cmd_node	*next_cmd;

	current_cmd = cmds;
	next_cmd = current_cmd->next;
	while (next_cmd)
	{
		if (next_cmd->type == PIPE && current_cmd->output_fd == STDOUT && next_cmd->input_fd == STDIN)
		{
			if (pipe(pipe_fds) < 0)
			{
				close_all_fds(cmds);
				display_error_message("Failed to create pipe");
				return (ERROR);
			}
			current_cmd->output_fd = pipe_fds[1];
			next_cmd->input_fd = pipe_fds[0];
		}
		current_cmd = next_cmd;
		next_cmd = next_cmd->next;
	}
	return (SUCCESS);
}

int	prepare_all_redirections(t_cmd_node *cmds)
{
	t_cmd_node	*current_cmd;

	current_cmd = cmds;
	while (current_cmd)
	{
		if (prepare_command_redirections(current_cmd, &current_cmd->input_fd, &current_cmd->output_fd))
			return (ERROR);
		current_cmd = current_cmd->next;
	}
	if (prepare_pipe_redirections(cmds))
		return (ERROR);
	return (SUCCESS);
}

void	execute_one_command(char **argv, t_shell *shell, int input_fd, int output_fd, pid_t *pid)
{
	if (argv[0] == NULL)
		return ;
	if (is_builtin_command(argv[0], shell->our_commands))
		execute_builtin_command(argv, shell);
	else if (ft_strchr(argv[0], '/') != NULL)
		execute_binary_with_path(argv, shell, input_fd, output_fd, pid);
	else
		execute_linux_command(argv, shell, input_fd, output_fd, pid);
}

void	init_input_output_fds(t_cmd_node *cmds)
{
	t_cmd_node	*current_cmd;

	current_cmd = cmds;
	while (current_cmd)
	{
		current_cmd->input_fd = STDIN;
		current_cmd->output_fd = STDOUT;
		current_cmd = current_cmd->next;
	}
}

int	count_commands(t_cmd_node *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	execute_pipeline(t_cmd_node *cmds, t_shell *shell)
{
	t_cmd_node	*current_cmd;
	pid_t	*pids;
	int	commands_count;
	//int	status;
	int	i;

	commands_count = count_commands(cmds);
	pids = malloc(sizeof(pid_t) * commands_count);
	i = 0;
	current_cmd = cmds;
	while (i < commands_count)
	{
		execute_one_command(current_cmd->argv, shell, current_cmd->input_fd, current_cmd->output_fd, &pids[i]);
		current_cmd = current_cmd->next;
		i++;
	}
	i = 0;
	current_cmd = cmds;
	while (i < commands_count)
	{
		if (current_cmd->input_fd != STDIN)
			close(current_cmd->input_fd);
		if (current_cmd->output_fd != STDOUT)
			close(current_cmd->output_fd);
		waitpid(pids[i], NULL, 0);
		i++;
		current_cmd = current_cmd->next;
	}
}

void	execute_sequence_of_commands(t_cmd_node *cmds, t_shell *shell)
{
	(void)shell;
	if (cmds == NULL)
		return ;
	init_input_output_fds(cmds);
	// handle_heredoc_redirections(cmds, shell);
	if (prepare_all_redirections(cmds) == ERROR)
		return ;
	execute_pipeline(cmds, shell);
}
