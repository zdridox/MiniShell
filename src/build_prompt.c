/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:53:50 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/26 04:13:18 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_parent_dir(char *path)
{
	char	*parent;
	int		i;

	i = ft_strlen(path) - 1;
	while (path[i] != '/' && i > 0)
		i--;
	parent = ft_substr(path, 0, i);
	free(path);
	return (parent);
}

int	is_git_repo(t_shell *shell)
{
	char	*path;
	char	*git_path;

	path = ft_strdup(get_env_value("PWD", shell->env));
	if (!path)
		error_exit("Failed to allocate memory", shell);
	while (ft_strcmp(path, "/") == EQUAL)
	{
		git_path = ft_strjoin(path, "/.git");
		if (access(git_path, F_OK) == EXIST)
		{
			free(git_path);
			free(path);
			return (TRUE);
		}
		path = get_parent_dir(path);
		if (!path)
			error_exit("Failed to allocate memory", shell);
	}
	return (FALSE);
}
char	*build_git_prompt(t_shell *shell)
{
	char	*git_prompt;

	(void)shell;
	git_prompt = ft_strdup(" (git) ");
	return (git_prompt);
}

char	*build_prompt(t_shell *shell)
{
	char	*prompt;
	char	*git_prompt;

	if (is_git_repo(shell))
	{
		git_prompt = build_git_prompt(shell);
		if (!git_prompt)
			error_exit("Failed to build git prompt", shell);
		prompt = ft_strjoin_many(7, GREEN, " ➜ ", BLUE,
			get_current_dir_name(shell), RESET, git_prompt, ORANGE,
			" ✗ ", RESET);
	}
	else
	{
		prompt = ft_strjoin_many(6, GREEN, " ➜ ", BLUE,
			get_current_dir_name(shell), ORANGE, " ✗ ", RESET);
	}
	if (!prompt)
		error_exit("Failed to build prompt", shell);
	free(git_prompt);
	return (prompt);
}

