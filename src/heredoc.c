/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:53:31 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/30 18:23:51 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long	hash_ulong(unsigned long x)
{
	x ^= x >> 16;
	x *= 0x7feb352d;
	x ^= x >> 15;
	x *= 0x846ca68b;
	x ^= x >> 16;
	return (x);
}

static unsigned long	generate_random_number(void *seed)
{
	long	random_number;

	random_number = hash_ulong((long)seed);
	return (random_number);
}

char	*generate_temp_file_path(void *seed)
{
	char			*temp_dir;
	char			*temp_file_name;
	char			*temp_file_path;
	unsigned long	random_number;

	temp_dir = "/tmp/minishell_heredoc_";
	random_number = generate_random_number(seed);
	temp_file_name = ft_ultoa(random_number);
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
			break ;
		}
		write(file_fd, line, ft_strlen(line));
		write(file_fd, "\n", 1);
		free(line);
	}
	close(file_fd);
	return (true);
}
