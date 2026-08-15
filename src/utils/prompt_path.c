/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 19:12:43 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 22:07:20 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*get_current_absolute_path(t_shell *shell)
{
	char	*absolute_path;

	absolute_path = get_env_value("PWD", shell->env);
	if (absolute_path)
		return (ft_strdup(absolute_path));
	else
		return (getcwd(NULL, 0));
}

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

static char	*get_current_dir_name(t_shell *shell)
{
	char	*current_dir_name;
	char	*absolute_pathname;
	int		last_slash_index;

	absolute_pathname = get_env_value("PWD", shell->env);
	absolute_pathname = ft_strdup(absolute_pathname);
	if (!absolute_pathname)
		absolute_pathname = getcwd(NULL, 0);
	if (ft_strcmp(absolute_pathname, "/") == 0)
		return (absolute_pathname);
	last_slash_index = ft_strlen(absolute_pathname) - 1;
	while (absolute_pathname[last_slash_index] != '/')
		last_slash_index--;
	current_dir_name = ft_strdup(absolute_pathname + last_slash_index + 1);
	free(absolute_pathname);
	return (current_dir_name);
}

bool	append_directory_to_prompt(t_dynamic_string *prompt, t_shell *shell)
{
	char	*dir_name;

	dir_name = get_current_dir_name(shell);
	if (!append_prompt_text(prompt, dir_name, BLUE))
		return (free(dir_name), false);
	free(dir_name);
	return (true);
}
