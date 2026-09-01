/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:50:30 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/02/03 12:42:58 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		find_char(char *str, char c);
char	*ft_str_merge(char *str1, char *str2);
char	*extract_line(char *str);
char	*extract_remainder(char *str);
char	*read_line(int fd, char *stash);

#endif
