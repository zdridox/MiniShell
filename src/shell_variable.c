#include "../headers/minishell.h"

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

int is_shell_var(char *input)
{
    char *input_trimmed;
    size_t equal_sign_index;
    size_t brace_sign_index;
    size_t double_brace_sign_index;
    size_t whitespace_index;

    input_trimmed = ft_strtrim(input, (char[]){9, 10, 11, 12, 13, 32, 0});
    whitespace_index = strchraindex(input_trimmed, (char[]){9, 10, 11, 12, 13, 32, 0});
    equal_sign_index = strchraindex(input_trimmed, "=");
    brace_sign_index = strchraindex(input_trimmed, "'");
    double_brace_sign_index = strchrindex(input_trimmed, "\"");
    if (whitespace_index < equal_sign_index || brace_sign_index < equal_sign_index || double_brace_sign_index < equal_sign_index || equal_sign_index == 0)
        return (free(input_trimmed), 0);
    return (free(input_trimmed), 1);
}

int is_shell_var_valid(char *sv)
{
    size_t i;
    char *sv_trimmed;
    size_t sv_trimmed_len;
    size_t equal_sign_index;
    const char illegal_name_chars[38] = {
        ' ', '\t', '\n', '\r', '\v', '\f',
        '-', '+', '.', ',', '!', '@', '#', '$', '%', '^', '&', '*',
        '(', ')', '[', ']', '{', '}', '|', '\\', '/', '=', ':', ';', '\'', '"', '<', '>', '?', '`', '~', 0};

    sv_trimmed = ft_strtrim(sv, (char[]){9, 10, 11, 12, 13, 32, 0});
    equal_sign_index = strchraindex(sv_trimmed, "=");
    sv_trimmed_len = ft_strlen(sv_trimmed);
    // check for digits at first char of var name cause they be illegal
    if (strchraindex(sv_trimmed, (char[]){'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0}) == 0)
        return (free(sv_trimmed), 0);
    // check for them illegal chars in the var name
    if (strchraindex(sv_trimmed, illegal_name_chars) < equal_sign_index)
        return (free(sv_trimmed), 0);
    // make sure quotes are closed and used correctly this is enough cause we dont handle escaping
    if (sv_trimmed[equal_sign_index + 1] == '"' || sv_trimmed[equal_sign_index + 1] == '\'')
    {
        if (sv_trimmed[sv_trimmed_len - 1] != sv_trimmed[equal_sign_index + 1])
            return (free(sv_trimmed), 0);
        i = equal_sign_index + 2;
        while (sv_trimmed[i])
        {
            if (sv_trimmed[i] == sv_trimmed[equal_sign_index + 1] && sv_trimmed[i + 1] != '\0')
                return (free(sv_trimmed), 0);
            ++i;
        }
    }
    // check for whitespace after '=' and no quotes thats illegal would be spread out to many tokens
    i = equal_sign_index + 1;
    while (sv_trimmed[i])
    {
        if (ft_is_space(sv_trimmed[i]) && (sv_trimmed[equal_sign_index + 1] != '"' && sv_trimmed[equal_sign_index + 1] != '\''))
            return (free(sv_trimmed), 0);
        ++i;
    }
    return (free(sv_trimmed), 1);
}
