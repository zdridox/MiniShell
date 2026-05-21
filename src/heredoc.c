#include "../headers/minishell.h"

long rng(char *seed) // lol shitty but its enough at least for now
{
    static long first_number = 0;
    static long number = 0;
    static int n = 0;
    const long magic = 6700;
    const long magic_2 = 7;

    if (number == 0 || first_number != (long)seed)
    {
        first_number = (long)seed;
        number = (long)seed;
        n = 0;
    }

    number /= magic_2;
    number += magic * (number % 10);
    number *= 10;
    if (n == 13)
    {
        number /= 100;
        n = 0;
    }
    ++n;
    return (number);
}

char *ltoa(long number)
{
    char *str;
    long num;
    int count;
    int i;

    if (number == 0)
        return (ft_strdup("0"));
    if (number < 0) // for now its enough lol
        number *= -1;
    i = 0;
    num = number;
    count = 0;
    while (num > 0)
    {
        ++count;
        num /= 10;
    }
    num = number;
    str = malloc(count + 1);
    str[count] = 0;
    while (num > 0)
    {
        str[count - i - 1] = '0' + (num % 10);
        num /= 10;
        ++i;
    }
    return (str);
}

int heredoc_fd(char *EOI)
{
    char *out;
    char *line;
    char *compare;
    int file_fd;
    char *random;

    random = ltoa(rng(EOI));
    file_fd = open(random, O_CREAT | O_RDWR | O_TRUNC, 0644);
    // out = ft_strdup("");
    line = ft_strdup("");
    compare = ft_strjoin(EOI, "\n");
    while (1)
    {
        free(line);
        ft_printf("heredoc> ");
        line = get_next_line(0);
        if (!ft_strncmp(line, compare, ft_strlen(line)) || !ft_strncmp(line, EOI, ft_strlen(line)))
        {
            free(line);
            break;
        }
        // safe_cat(&out, line);
        write(file_fd, line, ft_strlen(line));
    }
    free(compare);
    free(random);
    return (file_fd);
}

int main()
{
    // for (size_t i = 0; i < 1000; i++)
    // {
    //     long num = rng("sraka wilkolaka");
    //     printf("%ld, %s\n", num, ltoa(num));
    // }

    // int fd = heredoc_fd("dupa");
}

// old no save to file type shi
// void safe_cat(char **line, char *buffer) // podjebane z GNL z egzaminu XD
// {
//     char *new_line;
//     int index = 0;
//     int move_index = 0;

//     new_line = malloc(ft_strlen(*line) + ft_strlen(buffer) + 1);
//     while ((*line)[move_index])
//     {
//         new_line[index] = (*line)[move_index];
//         ++move_index;
//         ++index;
//     }
//     move_index = 0;
//     while (buffer[move_index])
//     {
//         new_line[index] = buffer[move_index];
//         ++move_index;
//         ++index;
//     }
//     new_line[index] = 0;
//     free(*line);
//     *line = new_line;
// }

// char *heredoc(char *EOI)
// {
//     char *out;
//     char *line;
//     char *compare;

//     out = ft_strdup("");
//     line = ft_strdup("");
//     compare = ft_strjoin(EOI, "\n");
//     while (1)
//     {
//         free(line);
//         ft_printf("heredoc> ");
//         line = get_next_line(0);
//         if (!ft_strncmp(line, compare, ft_strlen(line)))
//         {
//             free(line);
//             break;
//         }
//         safe_cat(&out, line);
//     }
//     free(compare);
//     return (out);
// }

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//         return (1);
//     char *heredoc_test = heredoc(argv[1]);
//     printf("%s", heredoc_test);
//     free(heredoc_test);
//     return (0);
// }