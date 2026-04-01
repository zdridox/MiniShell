#include "../headers/minishell.h"

void safe_cat(char **line, char *buffer) // podjebane z GNL z egzaminu XD
{
    char *new_line;
    int index = 0;
    int move_index = 0;

    new_line = malloc(ft_strlen(*line) + ft_strlen(buffer) + 1);
    while ((*line)[move_index])
    {
        new_line[index] = (*line)[move_index];
        ++move_index;
        ++index;
    }
    move_index = 0;
    while (buffer[move_index])
    {
        new_line[index] = buffer[move_index];
        ++move_index;
        ++index;
    }
    new_line[index] = 0;
    free(*line);
    *line = new_line;
}

char *heredoc(char *EOI)
{
    char *out;
    char *line;
    char *compare;

    out = ft_strdup("");
    line = ft_strdup("");
    compare = ft_strjoin(EOI, "\n");
    while (1)
    {
        free(line);
        line = get_next_line(0);
        if (!ft_strncmp(line, compare, ft_strlen(line)))
        {
            free(line);
            break;
        }
        safe_cat(&out, line);
    }
    return (out);
}

// int main()
// {
//     char *heredoc_test = heredoc("DUPA");
//     printf("%s", heredoc_test);
//     free(heredoc_test);
//     return (0);
// }