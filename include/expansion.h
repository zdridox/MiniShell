/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:20:19 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/24 20:43:24 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# define INITIAL_DYNAMIC_STRING_CAPACITY 100
# define QUOTED_WILDCARD -1

# include <dirent.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "libft.h"
// for development:
# include <stdio.h>
# include <string.h>
//#include <sys/types.h>
//#include <libgen.h>

typedef struct s_dynamic_string
{
	char	*string;
	size_t	size;
	size_t	capacity;
}			t_dynamic_string;

void		display_error_message(const char *error_message);

// dynamic_string.c
bool		init_dynamic_string(t_dynamic_string *dynamic_string,
				size_t inital_cappacity);
bool		resize_dynamic_string(t_dynamic_string *dynamic_string,
				size_t new_capacity);
bool		add_string_to_dynamic_string(char *string,
				t_dynamic_string *dynamic_string);
bool		add_char_to_dynamic_string(char c,
				t_dynamic_string *dynamic_string);
bool		add_n_chars_to_dynamic_string(char *string, size_t string_len,
				t_dynamic_string *dynamic_string);

// dynamic_string_int.c
bool		append_int_to_dynamic_string(int num,
				t_dynamic_string *dynamic_string);

// dynamic_string_convert.c
char		**convert_dynamic_string_to_str_arr(
				t_dynamic_string *dynamic_string);

// wildcard_expansion.c
bool		expand_wildcard(char *pattern, t_dynamic_string *matchaes);

// str_utilities.c
char		*ft_strjoin_three(const char *s1, const char *s2, const char *s3);

// parser_new.c
void		free_argv(char **argv);

#endif
