/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/04/09 21:52:57 by mamelnyk         ###   ########.fr       */
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

void	execute_linux_command(char **tokens, t_shell *shell, int input_fd, int output_fd)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(tokens[0], shell);
	if (bin_path == NULL)
	{
		// display_error_message("Command not found");
		printf("minishell: command not found: %s\n", tokens[0]);
		return ;
	}
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
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
	waitpid(pid, NULL, 0);
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

void	execute_binary_with_path(char **tokens, t_shell *shell)
{
	pid_t	pid;
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
	{
		execve(tokens[0], tokens, shell->env);
		error_exit("Command execution failed", shell);
	}
	waitpid(pid, NULL, 0);
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
int	handle_redirections(t_flag_node *flags, int *input_fd, int *output_fd, t_shell *shell)
{
	t_flag_node	*current_flag;

	current_flag = flags;
	while (current_flag != NULL)
	{
		if (current_flag->flag == READ_FROM_FILE)
		{
			if (*input_fd != STDIN)
				close(*input_fd);
			*input_fd = open(current_flag->flag_arg, O_RDONLY);
			if (*input_fd < 0)
				display_error_message("Failed to open input file");
			return (1);
		}
		if (current_flag->flag == OVERWRITE)
		{
			if (*output_fd != STDOUT)
				close(*output_fd);
			*output_fd = open(current_flag->flag_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*output_fd < 0)
				error_exit("Failed to open output file", shell);
		}
		if (current_flag->flag == APPEND)
		{
			if (*output_fd != STDOUT)
				close(*output_fd);
			*output_fd = open(current_flag->flag_arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*output_fd < 0)
				error_exit("Failed to open output file", shell);
		}
		current_flag = current_flag->next;
	}
	return (0);
}

void	execute_one_command(char **argv, t_shell *shell, int input_fd, int output_fd)
{
	if (argv[0] == NULL)
		return ;
	if (is_builtin_command(argv[0], shell->our_commands))
		execute_builtin_command(argv, shell);
	else if (ft_strchr(argv[0], '/') != NULL)
		execute_binary_with_path(argv, shell);
	else
		execute_linux_command(argv, shell, input_fd, output_fd);
}

void	execute_sequence_of_commands(t_cmd_node *cmds, t_shell *shell)
{
	int		input_fd;
	int		output_fd;
	//char	*input_file;

	input_fd = STDIN;
	output_fd = STDOUT;
	if (cmds == NULL)
		return ;
	if (cmds->flags)
	{
		if (handle_redirections(cmds->flags, &input_fd, &output_fd, shell))
			return ;
	}
	while (cmds)
	{
		execute_one_command(cmds->argv, shell, input_fd, output_fd);
		cmds = cmds->next;
	}
}
