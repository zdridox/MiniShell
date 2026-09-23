#include "minishell.h"

int strchraindex(char *str, const char *set) // get index of first apperance of any char from set in str
{
    size_t i;
    size_t j;

    i = 0;
    while (str[i])
    {
        j = 0;
        while (set[j])
        {
            if (str[i] == set[j])
                return (i);
            ++j;
        }
        ++i;
    }
    return (-1);
}

int	validate_svar_name(const char *inc, char *name)
{
	if (strchraindex(name, (char[]){'0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', 0}) == 0)
		return (0);
    if (strchraindex(name, inc) != -1)
        return (0);
    return (1);
}

int	validate_svar(char *name)
{
	int			res;
	static char	illegal_name_chars[38] = {' ', '\t', '\n', '\r', '\v', '\f',
			'-', '+', '.', ',', '!', '@', '#', '$', '%', '^', '&', '*', '(',
			')', '[', ']', '{', '}', '|', '\\', '/', '=', ':', ';', '\'', '"',
			'<', '>', '?', '`', '~', 0};

	res = 0;
	res += validate_svar_name(illegal_name_chars, name);
	if (res != 1)
		return (0);
	return (1);
}