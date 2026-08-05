/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:31:07 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/29 16:31:30 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

char	*skip_after_slash(char *pattern)
{
	return (ft_strchr(pattern, '/') + 1);
}

bool	is_last_char(char *pattern, char last_char)
{
	int	len;

	if (!pattern)
		return (false);
	len = ft_strlen(pattern);
	if (len > 0 && pattern[len - 1] == last_char)
		return (true);
	return (false);
}

char	*build_entry_full_path(char *dir_path, char *entry_name)
{
	char	*entry_full_path;

	if (ft_strcmp(dir_path, ".") == 0)
		entry_full_path = ft_strdup(entry_name);
	else if (ft_strcmp(dir_path, "/") == 0)
		entry_full_path = ft_strjoin("/", entry_name);
	else
		entry_full_path = ft_strjoin_three(dir_path, "/", entry_name);
	return (entry_full_path);
}
