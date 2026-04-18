/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:52:45 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/04/17 19:45:31 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_cmd_node *cmd, t_shell *shell, char *delimiter)
{
	char	*line;
	int		fd_temp_file;

	fd_temp_file = open("/tmp/.heredoc_temp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd_temp_file < 0)
	{
		// display_error_message("Failed to create temporary file for heredoc");
		return (ERROR);
	}
	line = readline("> ");
	while (line && ft_strcmp(line, delimiter) != EQUAL)
	{
		line = readline("> ");
		if (line == NULL)
		{
			// display_error_message("Unexpected EOF while reading heredoc");
			break ;
		}
		write(fd_temp_file, line, ft_strlen(line));
		write(fd_temp_file, "\n", 1);
		free(line);
		if (!line)
			break ;
	}
	return (SUCCESS);
}

int	main(void)
{
	char *delimiter = "END";
	int fd = heredoc(NULL, NULL, delimiter);
	if (fd < 0)
	{
		perror("Heredoc error");
		return (1);
	}
	printf("Heredoc content written to temporary file with fd: %d\n", fd);
	close(fd);
	return (0);
}
