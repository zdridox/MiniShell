/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:53:50 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/04/02 19:04:23 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_parent_dir(char *path)
{
	char	*parent;
	int		i;

	i = ft_strlen(path) - 1;
	while (path[i] != '/' && i > 1)
		i--;
	parent = ft_substr(path, 0, i);
	free(path);
	return (parent);
}

char	*find_git_repo(t_shell *shell)
{
	char	*path;
	char	*git_path;

	path = ft_strdup(get_env_value("PWD", shell->env));
	if (!path)
		return (free(path), error_exit("Failed to allocate memory", shell), NULL);
	while (ft_strcmp(path, "/") != EQUAL)
	{
		git_path = ft_strjoin(path, "/.git");
		if (!git_path)
			return (free(path), error_exit("Failed to allocate memory", shell), NULL);
		if (access(git_path, F_OK) == EXIST)
		{
			free(path);
			return (git_path);
		}
		path = get_parent_dir(path);
		if (!path)
			return (free(git_path), error_exit("Failed to allocate memory", shell), NULL);
		free(git_path);
	}
	free(path);
	return (NULL);
}

char	*get_git_branch(char *git_branch_path, t_shell *shell)
{
	char	*file_content;
	char	*git_branch;
	int		file_size;
	int		i;
	int		fd;

	if (access(git_branch_path, R_OK) != EXIST)
		return (NULL);
	fd = open(git_branch_path, O_RDONLY);
	file_content = get_next_line(fd);
	if (!file_content)
		error_exit("Failed to read git branch", shell);
	file_size = ft_strlen(file_content);
	i = file_size - 2;
	while (file_content[i] != '/' && i >= 0)
		i--;
	git_branch = ft_substr(file_content, i + 1, file_size - i - 2);
	free(file_content);
	if (!git_branch)
		error_exit("Failed to allocate memory", shell);
	return (git_branch);
}

char	*build_git_prompt(char *git_path, t_shell *shell)
{
	char	*git_prompt;
	char	*git_branch_path;
	char	*git_branch;

	git_branch_path = ft_strjoin(git_path, "/HEAD");
	if (!git_branch_path)
		error_exit("Failed to allocate memory", shell);
	if (access(git_branch_path, F_OK) == EXIST)
		git_branch = get_git_branch(git_branch_path, shell);
	else
		git_branch = ft_strdup("detached");
	if (!git_branch)
	{
		free(git_branch_path);
		error_exit("Failed to get git branch", shell);
	}
	git_prompt = ft_strjoin_many(7, PURPLE, " git:(", PINK,
		git_branch, PURPLE, ")", RESET);
	free(git_branch);
	free(git_branch_path);
	if (!git_prompt)
		error_exit("Failed to build git prompt", shell);
	return (git_prompt);
}

char	*build_prompt(t_shell *shell)
{
	char	*prompt;
	char	*git_prompt;
	char	*git_path;

	git_path = find_git_repo(shell);
	if (git_path)
	{
		git_prompt = build_git_prompt(git_path, shell);
		if (!git_prompt)
			return (free(git_path),
				error_exit("Failed to build git prompt", shell), NULL);
		prompt = ft_strjoin_many(9, GREEN, " ➜ ", BLUE,
			get_current_dir_name(shell), RESET, git_prompt, ORANGE,
			" ✗ ", RESET);
		free(git_prompt);
	}
	else
	{
		prompt = ft_strjoin_many(7, GREEN, " ➜ ", BLUE,
			get_current_dir_name(shell), ORANGE, " ✗ ", RESET);
	}
	if (!prompt)
		error_exit("Failed to build prompt", shell);
	return (prompt);
}

