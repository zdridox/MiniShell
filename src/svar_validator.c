#include "../headers/minishell.h"

int	validate_svar(char *name, char *value)
{
	int			res;
	static char	illegal_name_chars[38] = {' ', '\t', '\n', '\r', '\v', '\f',
			'-', '+', '.', ',', '!', '@', '#', '$', '%', '^', '&', '*', '(',
			')', '[', ']', '{', '}', '|', '\\', '/', '=', ':', ';', '\'', '"',
			'<', '>', '?', '`', '~', 0};

	res = 0;
	res += validate_svar_name(illegal_name_chars, name);
	res += validate_svar_value(illegal_name_chars, value);
	if (res != 2)
		return (0);
	return (1);
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

int	validate_svar_value(const char *inc, char *value)
{
}