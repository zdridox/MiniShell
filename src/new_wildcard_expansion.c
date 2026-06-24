#include "expansion.h"

bool	init_dynamic_string(t_dynamic_string *vector, size_t inital_cappacity)
{
	vector->size = 0;
	vector->capacity = inital_cappacity;
	vector->entries = malloc(vector->capacity * sizeof(char));
	if (vector->entries == NULL)
		return (false);
	vector->entries[0] = NULL;
	return (true);
}

char	**expand_wildcard(char *pattern)
{
	t_string_vector	matchaes;
	char			**result;

	if (!init_dynamic_string(&matchaes, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (NULL);
	if (pattern[0] == '/')
	{
		if (!find_matchaes_in_dir(pattern + 1, "/", &matchaes))
			return (free(matchaes.entries), NULL);
	}
	else
	{
		if (!find_matchaes_in_dir(pattern, ".", &matchaes))
			return (free(matchaes.entries), NULL);
	}
	result = convert_dynamic_string_to_str_arr(&matchaes);
	return (result);
}
