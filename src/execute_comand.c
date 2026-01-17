/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/17 15:43:44 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_bin_path(char *bin_name,t_shell *shell)
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
		error_exit("Memory allocation failed");
		// free shell
	i = 0;
	while (paths[i])
	{
		bin_path = ft_strjoin_three(paths[i], "/", bin_name);
		if (bin_path == NULL)
			error_exit("Memory allocation failed");
			// free paths and shell
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

void	execute_comand(t_shell *shell, char **tokens)
{
	pid_t	pid;
	char	*bin_path;

	bin_path = find_bin_path(tokens[0], shell);
	if (bin_path == NULL)
	{
		ft_putstr_fd("Command not found\n", STDERR);
		return ;
	}
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process");
		// free shell
	else if (pid == 0)
	{
		execve(bin_path, tokens, shell->env);
		ft_putstr_fd("Command execution failed\n", STDERR);
	}
	waitpid(pid, NULL, 0);
}
