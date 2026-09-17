/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:19:49 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/29 21:57:22 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <dirent.h>

static bool	handle_match(char *entry_full_path, char *pattern,
				bool pattern_has_slash, t_dynamic_string *matchaes);

static bool	add_matchaes_in_dir(DIR	*dir, char *pattern,
				char *dir_path, t_dynamic_string *matchaes)
{
	struct dirent	*entry;
	char			*entry_full_path;
	bool			pattern_has_slash;

	pattern_has_slash = ft_strchr(pattern, '/') != NULL;
	while (true)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (!is_valid_match(entry->d_name, pattern))
			continue ;
		entry_full_path = build_entry_full_path(dir_path, entry->d_name);
		if (!handle_match(entry_full_path, pattern, pattern_has_slash,
				matchaes))
		{
			free(entry_full_path);
			return (false);
		}
		free(entry_full_path);
	}
	return (true);
}

// better to rewrite it to not make allocations for each entry
static bool	find_matchaes_in_dir(char *pattern, char *dir_path,
		t_dynamic_string *matchaes)
{
	DIR				*dir;

	dir = opendir(dir_path);
	if (!dir)
		return (display_error_message("Failed to open dir"), false);
	if (!add_matchaes_in_dir(dir, pattern, dir_path, matchaes))
	{
		closedir(dir);
		return (false);
	}
	closedir(dir);
	return (true);
}

static bool	handle_directory(char *entry_full_path, char *pattern,
		t_dynamic_string *matchaes)
{
	if (is_last_char(pattern, '/'))
	{
		if (!add_n_chars_to_dynamic_string(entry_full_path,
				ft_strlen(entry_full_path), matchaes))
			return (false);
		if (!add_char_to_dynamic_string('/', matchaes))
			return (false);
		if (!add_char_to_dynamic_string('\0', matchaes))
			return (false);
	}
	if (!find_matchaes_in_dir(skip_after_slash(pattern), entry_full_path,
			matchaes))
		return (false);
	return (true);
}

static bool	handle_match(char *entry_full_path, char *pattern,
		bool pattern_has_slash, t_dynamic_string *matchaes)
{
	if (is_directory(entry_full_path) && pattern_has_slash)
	{
		if (handle_directory(entry_full_path, pattern, matchaes) == false)
			return (false);
	}
	else if (!pattern_has_slash
		&& !add_string_to_dynamic_string(entry_full_path, matchaes))
		return (false);
	return (true);
}

bool	expand_wildcard(char *pattern, t_dynamic_string *matchaes)
{
	if (pattern[0] == '/')
	{
		if (!find_matchaes_in_dir(pattern + 1, "/", matchaes))
			return (false);
	}
	else
	{
		if (!find_matchaes_in_dir(pattern, ".", matchaes))
			return (false);
	}
	return (true);
}
