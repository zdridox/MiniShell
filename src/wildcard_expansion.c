/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:24:36 by maxim             #+#    #+#             */
/*   Updated: 2026/07/04 19:45:36 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	match_pattern(char *entry_name, char *pattern);

bool	handle_wildcard(char *entry_name, char *pattern)
{
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0' || *pattern == '/')
		return (true);
	while (*entry_name)
	{
		if (*entry_name == *pattern || (*pattern == QUOTED_WILDCARD  && *entry_name == '*'))
		{
			if (match_pattern(entry_name + 1, pattern + 1))
				return (true);
		}
		entry_name++;
	}
	return (false);
}

bool	match_pattern(char *entry_name, char *pattern)
{
	if (*pattern == '\0')
		return (*entry_name == '\0');
	if (*pattern == '/' && *entry_name == '\0')
		return (true);
	if (*pattern == '*')
		return (handle_wildcard(entry_name, pattern));
	else if (*pattern == *entry_name || (*pattern == QUOTED_WILDCARD  && *entry_name == '*'))
		return (match_pattern(entry_name + 1, pattern + 1));
	return (false);
}

bool	is_valid_match(char *entry_name, char *pattern)
{
	if (*entry_name == '.' && *pattern != '.')
		return (false);
	return (match_pattern(entry_name, pattern));
}

bool	is_directory(const char *path)
{
	struct stat path_stat;

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

bool	find_matchaes_in_dir(char *pattern, char *dir_path, t_dynamic_string *matchaes);

bool	handle_directory(char *entry_full_path, char *pattern, t_dynamic_string *matchaes)
{
	if (is_last_char(pattern, '/'))
	{
		// or write function to add string without null terminator to dynamic string
		if (!add_n_chars_to_dynamic_string(entry_full_path, ft_strlen(entry_full_path), matchaes))
			return (false);
		if (!add_char_to_dynamic_string('/', matchaes))
			return (false);
		if (!add_char_to_dynamic_string('\0', matchaes))
			return (false);
	}
	if (!find_matchaes_in_dir(skip_after_slash(pattern), entry_full_path, matchaes))
		return (false);
	return (true);
}

bool	handle_match(char *entry_full_path, char *pattern, bool pattern_has_slash, t_dynamic_string *matchaes)
{
	if (is_directory(entry_full_path) && pattern_has_slash)
	{
		if (handle_directory(entry_full_path, pattern, matchaes) == false)
			return (false);
	}
	else if (!pattern_has_slash && !add_string_to_dynamic_string(entry_full_path, matchaes))
		return (false);
	return (true);
}

// better to rewrite it to not make allocations for each entry
bool	find_matchaes_in_dir(char *pattern, char *dir_path, t_dynamic_string *matchaes)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*entry_full_path;
	bool			pattern_has_slash;

	dir = opendir(dir_path);
	if (!dir)
	{
		//display_error_message("Failed to open dir");
		printf("Failed to open dir: %s\n", dir_path);
		return (false);
	}
	pattern_has_slash = ft_strchr(pattern, '/') != NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!is_valid_match(entry->d_name, pattern))
			continue ;
		entry_full_path = build_entry_full_path(dir_path, entry->d_name);
		if (!handle_match(entry_full_path, pattern, pattern_has_slash, matchaes))
		{
			free(entry_full_path);
			closedir(dir);
			return (false);
		}
		free(entry_full_path);
	}
	closedir(dir);
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
/*
int	main(int argc, char **argv)
{
	t_dynamic_string	expanded;
	int	i;

	if (!init_dynamic_string(&expanded, 100))
	{
		printf("Failed to initialize dynamic string.\n");
		return (1);
	}
	if (argc != 2)
	{
		printf("Usage: %s <pattern>\n", argv[0]);
		return (1);
	}
	if (strchr(argv[1], '*') == NULL)
	{
		printf("No wildcard found in pattern.\n");
		return (1);
	}
	if (!expand_wildcard(argv[1], &expanded))
	{
		printf("Wildcard expansion failed.\n");
		return (1);
	}
	i = 0;
	argv = convert_dynamic_string_to_str_arr(&expanded);
	if (!argv)
	{
		printf("Failed to convert dynamic string to string array.\n");
		return (1);
	}
	while (argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
	free(argv[0]);
	free(argv);
	return (0);
}
*/
