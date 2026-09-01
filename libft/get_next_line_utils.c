/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:49:28 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/11/15 20:40:25 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_char(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_str_merge(char *str1, char *str2)
{
	char	*merged_str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = 0;
	len2 = 0;
	while (str1 && str1[len1])
		len1++;
	while (str2[len2])
		len2++;
	merged_str = malloc(len1 + len2 + 1);
	if (!merged_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		merged_str[i] = str1[i];
	free(str1);
	j = 0;
	while (j < len2)
		merged_str[i++] = str2[j++];
	merged_str[len1 + len2] = '\0';
	return (merged_str);
}

char	*extract_line(char *str)
{
	char	*line;
	int		newline_position;
	int		i;

	if (!str)
		return (NULL);
	newline_position = find_char(str, '\n');
	if (newline_position == -1)
		newline_position = find_char(str, '\0');
	line = (char *)malloc(newline_position
			+ (str[newline_position] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && i <= newline_position)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_remainder(char *str)
{
	char	*remainder;
	int		newline_char_position;
	int		remainder_size;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	newline_char_position = find_char(str, '\n');
	if (newline_char_position == -1)
		return (NULL);
	remainder_size = find_char(str + newline_char_position + 1, '\0') + 1;
	if (remainder_size <= 1)
		return (NULL);
	remainder = (char *)malloc(remainder_size);
	if (!remainder)
		return (NULL);
	i = 0;
	j = newline_char_position + 1;
	while (str[j])
	{
		remainder[i++] = str[j++];
	}
	remainder[i] = '\0';
	return (remainder);
}

char	*read_line(int fd, char *stash)
{
	ssize_t		bytes_readed;
	char		*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash), NULL);
	bytes_readed = 1;
	while (find_char(stash, '\n') == -1 && bytes_readed > 0)
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		if (bytes_readed < 0)
			return (free(buf), NULL);
		if (bytes_readed == 0)
			break ;
		buf[bytes_readed] = '\0';
		stash = ft_str_merge(stash, buf);
		if (!stash)
			return (free(buf), NULL);
	}
	return (free(buf), stash);
}
