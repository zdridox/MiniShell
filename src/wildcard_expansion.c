/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:24:36 by maxim             #+#    #+#             */
/*   Updated: 2026/06/24 18:43:21 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_strdup(const char *str)
{
	char	*duplicate;
	size_t	i;

	if (str == NULL)
		return (NULL);
	duplicate = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	if (duplicate == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

void free_str_arr(char **str_arr)
{
	unsigned int i;

	i = 0;
	if (!str_arr)
		return;
	while (str_arr[i])
	{
		free(str_arr[i++]);
	}
	free(str_arr);
}

bool	init_string_vector(t_string_vector *vector)
{
	vector->size = 0;
	vector->capacity = INITIAL_STRING_VECTOR_CAPACITY;
	vector->entries = malloc(sizeof(char *) * vector->capacity);
	if (vector->entries == NULL)
		return (false);
	vector->entries[0] = NULL;
	return (true);
}

bool	resize_string_vector(t_string_vector *vector)
{
	char	**new_entries;
	size_t	i;

	vector->capacity *= 2;
	new_entries = malloc(sizeof(char *) * vector->capacity);
	if (!new_entries)
	{
		free(vector->entries);
		vector->entries = NULL;
		return (false);
	}
	i = 0;
	while (i <= vector->size)
	{
		new_entries[i] = vector->entries[i];
		i++;
	}
	free(vector->entries);
	vector->entries = new_entries;
	return (true);
}

bool	add_string_to_vector(char *string, t_string_vector *vector)
{
	char	*new_string;

	if (vector->size + 1 >= vector->capacity)
	{
		if (!resize_string_vector(vector))
			return (false);
	}
	vector->entries[vector->size] = ft_strdup(string);
	vector->entries[vector->size + 1] = NULL;
	vector->size += 1;
	return (true);
}

bool	find_matchaes_in_dir(char *pattern, char *dir_name, t_string_vector *matchaes);

bool	match_pattern(char *pattern, char *file_name, int file_name_len, t_string_vector *matchaes)
{
	if (matchaes->entries == NULL)
		return (false);
	if (*pattern == '\0' && *file_name == '\0')
		return (true);
	if (*pattern == '\0' && *file_name != '\0')
		return (false);
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (*(pattern + 1) == '\0') // it is not necessaty because of the loop
			return (true);
		while (*file_name)
		{
			if (*(pattern + 1) == *file_name)
			{
				if (match_pattern(pattern + 1, file_name, file_name_len, matchaes))
					return (true);
			}
			file_name++;
		}
		if (*file_name == '\0' && *(pattern + 1) == '\0')
			return (true);
	}
	else if (*pattern == *file_name)
	{
		return (match_pattern(pattern + 1, file_name + 1, file_name_len, matchaes));
	}
	else if (*pattern == '/' && *file_name == '\0')
	{
		find_matchaes_in_dir(pattern + 1, file_name - file_name_len, matchaes);
		return (false);
	}
	return (false);
}

void	skip_pattern_prefix(char **pattern)
{
	while (**pattern && **pattern != '/')
		(*pattern)++;
	if (**pattern == '/')
		(*pattern)++;
}

bool	add_mathaes_with_prefix_to_matchaes(t_string_vector *matchaes, t_string_vector *matchaes_with_prefix, char *prefix)
{
	size_t	i;
	char	*added_path;

	i = 0;
	while (i < matchaes_with_prefix->size)
	{
		added_path = ft_strjoin(prefix, matchaes_with_prefix->entries[i]);
		if (!added_path)
			return (false);
		if (!add_string_to_vector(added_path, matchaes))
		{
			free(added_path);
			return (false);
		}
		free(added_path);
		i++;
	}
	return (true);
}

bool	find_matchaes_with_this_prefix(char *pattern, char *prefix, t_string_vector *prefix_matchaes)
{
	t_string_vector	matchaes_with_prefix;

	if (!init_string_vector(&matchaes_with_prefix))
		return (false);
	skip_pattern_prefix(&pattern);
	if (*pattern == '\0')
	{
		free(matchaes_with_prefix.entries);
		return (add_string_to_vector(prefix, prefix_matchaes));
	}
	if (!find_matchaes_in_dir(pattern, prefix, &matchaes_with_prefix))
	{
		free(matchaes_with_prefix.entries);
		return (false);
	}
	if (matchaes_with_prefix.size == 0)
	{
		free(matchaes_with_prefix.entries);
		return (true);
	}
	if (!add_mathaes_with_prefix_to_matchaes(prefix_matchaes, &matchaes_with_prefix, prefix))
	{
		free(matchaes_with_prefix.entries);
		return (false);
	}
	free(matchaes_with_prefix.entries);
	return (true);
}

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

bool	find_matchaes_in_dir(char *pattern, char *dir_name, t_string_vector *matchaes)
{
	DIR				*dir;
	struct dirent	*entrie;

	dir = opendir(dir_name);
	if (!dir)
	{
		display_error_message("Failed to open dir");
		return (false);
	}
	while ((entrie = readdir(dir)) != NULL)
	{
		if (*(entrie->d_name) == '.' && *pattern != '.')
			continue ;
		if (match_pattern(pattern, entrie->d_name, strlen(entrie->d_name), matchaes))
		{
			if (is_directory(entrie->d_name))
			{
				if (!find_matchaes_with_this_prefix(pattern, entrie->d_name, matchaes))
					return (false);
			}
			else if (!add_string_to_vector(entrie->d_name, matchaes))
				return (false);
		}
	}
	closedir(dir);
	return (true);
}

char	**expand_one_wildcard(char *pattern)
{
	t_string_vector	matchaes;

	if (!init_string_vector(&matchaes))
		return (NULL);
	if (pattern[0] == '/')
	{
		if (!find_matchaes_in_dir(pattern + 1, "/", &matchaes))
			return (NULL);
	}
	else
	{
		if (!find_matchaes_in_dir(pattern, ".", &matchaes))
			return (NULL);
	}
	return(matchaes.entries);
}

int	main(int argc, char **argv)
{
	char	**expanded;
	int		i;

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
	expanded = expand_one_wildcard(argv[1]);
	i = 0;
	while (expanded[i])
	{
		printf("%s\n", expanded[i]);
		i++;
	}
	free_str_arr(expanded);
	return (0);
}
