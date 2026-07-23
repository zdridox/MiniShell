#include "minishell.h"

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

static long hash_long(long x)
{
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68b;
    x ^= x >> 16;
    return (x);
}

long	generate_random_number(void *seed)
{
	long	random_number;

	random_number = hash_long((long)seed);
	return (random_number);
}

char *generate_temp_file_path(void *seed)
{
	char *temp_dir = "/tmp/minishell_heredoc_";
	char *temp_file_name;
	char *temp_file_path;
	long random_number;

	random_number = generate_random_number(seed);
	temp_file_name = ltoa(random_number);
	if (!temp_file_name)
	{
		display_error_message("Failed to allocate memory for temp file name");
		return (NULL);
	}
	temp_file_path = ft_strjoin(temp_dir, temp_file_name);
	free(temp_file_name);
	if (!temp_file_path)
	{
		display_error_message("Failed to allocate memory for temp file path");
		return (NULL);
	}
	return (temp_file_path);
}

bool	write_heredoc_to_file(char *delimiter, char *file_path)
{
    int		file_fd;
    char	*line;

    file_fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		display_error_message("Failed to open heredoc temp file");
		return (false);
	}
	while (true)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(file_fd, line, ft_strlen(line));
		write(file_fd, "\n", 1);
		free(line);
	}
	close(file_fd);
    return (true);
}

// int main()
// {
//     for (size_t i = 0; i < 1000; i++)
//     {
//         long num = rng("sraka wilkolaka");
//         printf("%ld, %s\n", num, ltoa(num));
//     }

//     // int fd = heredoc_fd("dupa");
//     // char *buff = malloc(100);
//     // int size = read(fd, buff, 10);
//     // buff[size] = 0;
//     // printf("\n\n%s\n", buff);
// }

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
