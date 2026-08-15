/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:53:50 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 21:55:49 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*build_prompt(t_shell *shell)
{
	t_dynamic_string	prompt;

	if (!init_dynamic_string(&prompt, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (display_error_message("Failed to allocate memory"), NULL);
	if (!append_arrow_to_prompt(&prompt, shell))
		return (free(prompt.string),
			display_error_message("Failed to build prompt"), NULL);
	if (!append_directory_to_prompt(&prompt, shell))
		return (free(prompt.string),
			display_error_message("Failed to build prompt"), NULL);
	if (!append_git_segment_to_prompt(&prompt, shell))
		return (free(prompt.string),
			display_error_message("Failed to build prompt"), NULL);
	if (!append_prompt_suffix(&prompt))
		return (free(prompt.string),
			display_error_message("Failed to build prompt"), NULL);
	return (prompt.string);
}
