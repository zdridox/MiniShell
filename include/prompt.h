/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 19:07:01 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/15 22:00:36 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# include "expansion.h"

// promt_path.c
char	*get_current_absolute_path(t_shell *shell);
char	*get_parent_dir(char *path);
bool	append_directory_to_prompt(t_dynamic_string *prompt, t_shell *shell);

// prompt_git_find.c
char	*find_git_metadata_path(t_shell *shell);
bool	append_git_branch(char *git_metadata_path,
			t_dynamic_string *prompt);

// prompt_append.c
bool	append_prompt_text(t_dynamic_string *prompt,
			char *text, char *color);
bool	append_arrow_to_prompt(t_dynamic_string *prompt, t_shell *shell);
bool	append_git_segment_to_prompt(t_dynamic_string *prompt, t_shell *shell);
bool	append_prompt_suffix(t_dynamic_string *prompt);

#endif
