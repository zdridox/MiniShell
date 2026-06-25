#include "expansion.h"

bool	init_dynamic_string(t_dynamic_string *dynamic_string, size_t inital_cappacity)
{
	dynamic_string->size = 0;
	dynamic_string->capacity = inital_cappacity;
	dynamic_string->string = malloc(dynamic_string->capacity * sizeof(char));
	if (dynamic_string->string == NULL)
		return (false);
	return (true);
}

bool	resize_dynamic_string(t_dynamic_string *dynamic_string, size_t new_capacity)
{
	char	*new_string;

	new_string = malloc(new_capacity * sizeof(char));
	if (!new_string)
		return (false);
	ft_memcpy(new_string, dynamic_string->string, dynamic_string->size);
	free(dynamic_string->string);
	dynamic_string->string = new_string;
	dynamic_string->capacity = new_capacity;
	return (true);
}

bool	add_string_to_dynamic_string(char *string, t_dynamic_string *dynamic_string)
{
	size_t	string_len;
	size_t	needed_capacity;
	
	string_len = (size_t)ft_strlen(string);
	needed_capacity = dynamic_string->size + string_len + 1;
	if (dynamic_string->capacity > needed_capacity)
		ft_memcpy(dynamic_string->string + dynamic_string->size, string, string_len);
	else
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
		ft_memcpy(dynamic_string->string + dynamic_string->size, string, string_len);
	}
	dynamic_string->string[dynamic_string->size + string_len] = '\0';
	dynamic_string->size += string_len + 1;
	return (true);
}

bool	add_char_to_dynamic_string(char c, t_dynamic_string *dynamic_string)
{
	size_t	needed_capacity;

	needed_capacity = dynamic_string->size + 1;
	if (dynamic_string->capacity > needed_capacity)
		dynamic_string->string[dynamic_string->size] = c;
	else
	{
		if (!resize_dynamic_string(dynamic_string, needed_capacity * 2))
			return (false);
		dynamic_string->string[dynamic_string->size] = c;
	}
	dynamic_string->size += 1;
	return (true);
}

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
	else if (*pattern == *entry_name)
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

size_t	count_strings_in_dynamic_string(t_dynamic_string *dynamic_string)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < dynamic_string->size)
	{
		if (dynamic_string->string[i] == '\0')
			count++;
		i++;
	}
	return (count);
}

char	**convert_dynamic_string_to_str_arr(t_dynamic_string *dynamic_string)
{
	char	**str_arr;
	size_t	str_count;
	size_t	i;
	size_t	j;

	if (dynamic_string->size == 0)
		return (NULL);
	str_count = count_strings_in_dynamic_string(dynamic_string);
	str_arr = malloc((str_count + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < str_count)
	{
		str_arr[i] = &(dynamic_string->string[j]);
		j += ft_strlen(&(dynamic_string->string[j])) + 1;
		i++;
	}
	str_arr[str_count] = NULL;
	return (str_arr);
}

char	**expand_wildcard(char *pattern)
{
	t_dynamic_string	matchaes;
	char				**result;

	if (!init_dynamic_string(&matchaes, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (NULL);
	if (pattern[0] == '/')
	{
		if (!find_matchaes_in_dir(pattern + 1, "/", &matchaes))
			return (free(matchaes.string), NULL);
	}
	else
	{
		if (!find_matchaes_in_dir(pattern, ".", &matchaes))
			return (free(matchaes.string), NULL);
	}
	result = convert_dynamic_string_to_str_arr(&matchaes);
	if (!result)
		return (free(matchaes.string), NULL);
	return (result);
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
	expanded = expand_wildcard(argv[1]);
	i = 0;
	while (expanded[i])
	{
		printf("%s\n", expanded[i]);
		i++;
	}
	free(expanded);
	return (0);
}
