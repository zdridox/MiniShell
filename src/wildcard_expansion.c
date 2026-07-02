/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:24:36 by maxim             #+#    #+#             */
/*   Updated: 2026/07/02 15:29:50 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	match_pattern(char *entry_name, char *pattern);

bool	handle_wildcard(char *entry_name, char *pattern)
{
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0')
		return (true);
	while (*entry_name)
	{
		if (*entry_name == *pattern)
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

bool	find_matchaes_in_dir(char *pattern, char *dir_name, t_dynamic_string *matchaes)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dir_name);
	if (!dir)
	{
		//display_error_message("Failed to open dir");
		printf("Failed to open dir: %s\n", dir_name);
		return (false);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (!is_valid_match(entry->d_name, pattern))
			continue ;
		if (is_directory(entry->d_name) && ft_strchr(pattern, '/') != NULL)
		{
			if (!find_matchaes_in_dir(skip_after_slash(pattern), entry->d_name, matchaes))
				return (false);
		}
		else if (!add_string_to_dynamic_string(entry->d_name, matchaes))
			return (false);
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

	if (!init_dynamic_string(&expanded))
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
	if (expand_wildcard(argv[1], &expanded))
		printf("Wildcard expansion successful.\n");
	else
	{
		printf("Wildcard expansion failed.\n");
		return (1);
	}
	i = 0;
	argv = convert_dynamic_string_to_str_arr(&expanded);
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
	free(argv[0]);
	free(argv);
	return (0);
}
*/
