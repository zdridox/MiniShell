/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:47:02 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 22:11:50 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

bool	append_prompt_text(t_dynamic_string *prompt,
				char *text, char *color)
{
	if (!add_n_chars_to_dynamic_string(color, ft_strlen(color), prompt))
		return (false);
	if (!add_n_chars_to_dynamic_string(text, ft_strlen(text), prompt))
		return (false);
	return (true);
}

bool	append_arrow_to_prompt(t_dynamic_string *prompt, t_shell *shell)
{
	char	*arror_color;

	if (shell->last_exit_code == 0)
		arror_color = GREEN;
	else
		arror_color = RED;
	if (!append_prompt_text(prompt, " > ", arror_color))
		return (false);
	return (true);
}

bool	append_git_segment_to_prompt(t_dynamic_string *prompt, t_shell *shell)
{
	char	*git_metadata_path;

	git_metadata_path = find_git_metadata_path(shell);
	if (git_metadata_path)
	{
		if (!append_prompt_text(prompt, " git:(", PURPLE))
			return (free(git_metadata_path), false);
		if (!append_git_branch(git_metadata_path, prompt))
			return (free(git_metadata_path), false);
		if (!append_prompt_text(prompt, ")", PURPLE))
			return (free(git_metadata_path), false);
	}
	free(git_metadata_path);
	return (true);
}

bool	append_prompt_suffix(t_dynamic_string *prompt)
{
	if (!append_prompt_text(prompt, " $ ", ORANGE))
		return (false);
	if (!add_n_chars_to_dynamic_string(RESET, ft_strlen(RESET), prompt))
		return (false);
	if (!add_char_to_dynamic_string('\0', prompt))
		return (false);
	return (true);
}
