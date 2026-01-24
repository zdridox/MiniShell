/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/24 14:52:19 by anatoliy         ###   ########.fr       */
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

void	execute_linux_command(char **tokens, t_shell *shell)
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

void	execute_comand(char **tokens, t_shell *shell)
{
	if (tokens[0] == NULL)
		return ;
	if (is_builtin_command(tokens[0], shell->our_commands) == TRUE)
		execute_builtin_command(tokens, shell);
	else
		execute_linux_command(tokens, shell);
}
