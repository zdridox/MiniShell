/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 19:15:42 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 21:36:38 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*check_git_path(char *path)
{
	char	*git_path;

	git_path = ft_strjoin(path, "/.git");
	if (!git_path)
		return (display_error_message("Failed to allocate memory"), NULL);
	if (access(git_path, F_OK) == EXIST)
		return (git_path);
	free(git_path);
	return (NULL);
}

char	*find_git_metadata_path(t_shell *shell)
{
	char	*path;
	char	*git_path;

	path = get_current_absolute_path(shell);
	if (!path)
		return (free(path),
			display_error_message("Failed to get current absolute path"), NULL);
	while (ft_strcmp(path, "/") != EQUAL)
	{
		git_path = check_git_path(path);
		if (git_path)
			return (free(path), git_path);
		path = get_parent_dir(path);
		if (!path)
			return (free(git_path),
				display_error_message("Failed to allocate memory"), NULL);
		free(git_path);
	}
	free(path);
	return (NULL);
}
