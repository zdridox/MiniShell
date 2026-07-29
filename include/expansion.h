/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:20:19 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/29 19:19:17 by mamelnyk         ###   ########.fr       */
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
# include "minishell.h"

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

// env_expand.c
bool		expand_environment_variables(t_word *words, t_shell *shell);

// env_expand_utilities.c
bool		is_valid_variable_name_char(char c);
bool		is_last_exit_status_variable(char *str);
int			get_variable_name_length(const char *str);

// word_expand.c
int			get_word_length(t_word_part *word_parts);
char		**expand_to_argv(t_word *words, t_shell *shell);

// pattern_expand.c
bool		expand_wildcards_to_dynamic_string(t_word_part *word_parts,
				t_dynamic_string *dynamic_string);

// wildcard_expansion.c
bool		expand_wildcard(char *pattern, t_dynamic_string *matchaes);

// wildcard_match.c
bool		is_valid_match(char *entry_name, char *pattern);

// wildcard_search.c
bool		expand_wildcard(char *pattern, t_dynamic_string *matchaes);

// wildcard_utilities.c
bool		is_directory(const char *path);
char		*skip_after_slash(char *pattern);
bool		is_last_char(char *pattern, char last_char);
char		*build_entry_full_path(char *dir_path, char *entry_name);

#endif
