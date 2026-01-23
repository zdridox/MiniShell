/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/23 20:37:14 by mamelnyk         ###   ########.fr       */
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

int	is_builtin_command(char *command_name, t_shell *shell)
{
	while (shell->our_commands && shell->our_commands->name)
	{
		if (ft_strcmp(command_name, shell->our_commands->name) == EQUAL)
			return (TRUE);
		shell->our_commands++;
	}
	return (FALSE);
}

void	execute_linux_command(t_shell *shell, char **tokens)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(tokens[0], shell);
	if (bin_path == NULL)
	{
		display_error_message("Command not found");
		return ;
	}
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process", shell);
	else if (pid == CHILD_PROCESS)
	{
		execve(bin_path, tokens, shell->env);
		display_error_message("Command execution failed");
	}
	waitpid(pid, NULL, 0);
}

void	execute_builtin_command(t_shell *shell, char **tokens)
{
	while (shell->our_commands && shell->our_commands->name)
	{
		if (ft_strcmp(tokens[0], shell->our_commands->name) == EQUAL)
		{
			shell->our_commands->function(shell, tokens);
			return ;
		}
		shell->our_commands++;
	}
}

void	execute_comand(t_shell *shell, char **tokens)
{
	if (tokens[0] == NULL)
		return ;
	if (is_builtin_command(tokens[0], shell) == TRUE)
		execute_builtin_command(shell, tokens);
	else
		execute_linux_command(shell, tokens);
}
