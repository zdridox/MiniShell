/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git_branch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:37:21 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 21:59:12 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

// Could be optimized and refactored
static char	*get_git_branch(char *git_branch_path)
{
	char	*file_content;
	char	*git_branch;
	int		file_size;
	int		i;
	int		fd;

	if (access(git_branch_path, R_OK) != EXIST)
		return (NULL);
	fd = open(git_branch_path, O_RDONLY);
	if (fd < 0)
		return (display_error_message("Failed to open git branch file"), NULL);
	file_content = get_next_line(fd);
	close(fd);
	if (!file_content)
		return (display_error_message("Failed to read git branch file"), NULL);
	file_size = ft_strlen(file_content);
	i = file_size - 2;
	while (i >= 0 && file_content[i] != '/')
		i--;
	git_branch = ft_substr(file_content, i + 1, file_size - i - 2);
	free(file_content);
	if (!git_branch)
		return (display_error_message("Failed to allocate memory"), NULL);
	return (git_branch);
}

bool	append_git_branch(char *git_metadata_path,
				t_dynamic_string *prompt)
{
	char	*git_branch;
	char	*git_branch_path;

	git_branch_path = ft_strjoin(git_metadata_path, "/HEAD");
	if (!git_branch_path)
		return (display_error_message("Failed to allocate memory"), false);
	git_branch = get_git_branch(git_branch_path);
	if (!git_branch)
		return (free(git_branch_path), false);
	if (!append_prompt_text(prompt, git_branch, PINK))
		return (free(git_branch), free(git_branch_path), false);
	free(git_branch_path);
	free(git_branch);
	return (true);
}
