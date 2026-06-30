/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:18:34 by anatoliy          #+#    #+#             */
/*   Updated: 2026/06/30 21:40:32 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

bool	is_valid_env_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_last_exit_status_variable(char *str)
{
	if (!str || !str[0])
		return (false);
	return (str[0] == '?' && !is_valid_env_variable_char(str[1]));
}

int	get_variable_name_length(const char *str)
{
	int length = 0;

	while (str[length] && is_valid_env_variable_char(str[length]))
		length++;
	return (length);
}

bool	append_expanded_variable_to_dynamic_string(t_dynamic_string *dynamic_string, char *str, int *i, t_shell *shell)
{
	char	*var_value;
	int		var_name_length;

	(*i)++;
	if (is_last_exit_status_variable(str + *i))
		return (append_int_to_dynamic_string(shell->last_exit_code, dynamic_string));
	var_name_length = get_variable_name_length(str + *i);
	if (var_name_length == 0)
		return (add_char_to_dynamic_string('$', dynamic_string));
	var_value = get_env_value(str + *i, shell->env);
	if (!var_value)
		return (true);
	if (!add_string_to_dynamic_string(var_value, dynamic_string))
		return (false);
	*i += var_name_length;
	return (true);
}

char	*expand_environment_variables_in_string(char *str, t_shell *shell)
{
	t_dynamic_string	expanded_string;
	int			len;
	int			i;

	if (!init_dynamic_string(&expanded_string, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (NULL);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!add_n_chars_to_dynamic_string(&str[i - len], len, &expanded_string))
				return (free(expanded_string.string), NULL);
			if (!append_expanded_variable_to_dynamic_string(&expanded_string, str, &i, shell))
				return (free(expanded_string.string), NULL);
			len = 0;
		}
		else
			len++;
		i++;
	}
	if (!add_char_to_dynamic_string('\0', &expanded_string))
		return (free(expanded_string.string), NULL);
	return (expanded_string.string);
}

bool	expand_environment_variables_in_word(t_word_part *word_parts, t_shell *shell)
{
	char	*expanded_value;

	while (word_parts)
	{
		if ((word_parts->type == PLAIN || word_parts->type == DOUBLE_QUOTED)
			&& expand_environment_variables_in_string(word_parts->value, shell))
		{
			expanded_value = expand_environment_variables_in_string(word_parts->value, shell);
			if (!expanded_value)
				return (false);
			if (ft_strcmp(expanded_value, word_parts->value) != EQUAL)
			{
				free(word_parts->value);
				word_parts->value = expanded_value;
			}
			else
				free(expanded_value);
		}
		word_parts = word_parts->next;
	}
	return (true);
}

bool	expand_environment_variables(t_word *words, t_shell *shell)
{
	while (words)
	{
		if (!expand_environment_variables_in_word(words->word_parts, shell))
			return (false);
		words = words->next;
	}
	return (true);
}

bool	expand_word_to_dynamic_string(t_word_part *word_parts, t_dynamic_string *dynamic_string)
{
		while (word_parts)
		{
			if (!add_string_to_dynamic_string(word_parts->value, dynamic_string))
				return (false);
			word_parts = word_parts->next;
		}
		return (true);
}

int	get_word_length(t_word_part *word_parts)
{
	int	length;

	length = 0;
	while (word_parts)
	{
		length += ft_strlen(word_parts->value);
		word_parts = word_parts->next;
	}
	return (length);
}

void	replace_quoted_wildcards_in_string(char *str)
{
	while (*str)
	{
		if (*str == '*')
			*str = QUOTED_WILDCARD;
		str++;
	}
}

void	replace_qutoed_wildcards_in_word(t_word_part *word_parts)
{
	if (word_parts->type != PLAIN)
		return ;
	while (word_parts)
	{
		if (word_parts->type == PLAIN)
			replace_quoted_wildcards_in_string(word_parts->value);
		word_parts = word_parts->next;
	}
}

char	*convert_word_to_pattern(t_word_part *word_parts)
{
		char	*pattern;
		int		pattern_length;
		int		pattern_index;
		int		string_length;

		pattern_length = get_word_length(word_parts);
		pattern = malloc(pattern_length + 1);
		if (!pattern)
			return (NULL);
		replace_qutoed_wildcards_in_word(word_parts);
		pattern_index = 0;
		while (word_parts)
		{
			string_length = ft_strlen(word_parts->value);
			ft_memcpy(pattern + pattern_index, word_parts->value, string_length);
			pattern_index += string_length;
			word_parts = word_parts->next;
		}
		pattern[pattern_length] = '\0';
		return (pattern);
}

bool	expand_wildcards_to_dynamic_string(t_word_part *word_parts, t_dynamic_string *dynamic_string)
{
		char	*pattern;

		pattern = convert_word_to_pattern(word_parts);
		if (!pattern)
			return (false);
		if (!expand_wildcard(pattern, dynamic_string))
			return (free(pattern), false);
		free(pattern);
		return (true);
}

bool	is_wildcard_present_in_word(t_word_part *word_parts)
{
	while (word_parts)
	{
		if (word_parts->type == PLAIN && ft_strchr(word_parts->value, '*') != NULL)
			return (true);
		word_parts = word_parts->next;
	}
	return (false);
}

char	**expand_to_argv(t_word *words, t_shell *shell)
{
	t_dynamic_string	argv_string;
	char				**argv;

	if (!words || !shell)
		return (NULL);
	if (!expand_environment_variables(words, shell))
		return (NULL);
	if (!init_dynamic_string(&argv_string, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (NULL);
	while (words)
	{
		if (is_wildcard_present_in_word(words->word_parts))
		{
			if (!expand_wildcards_to_dynamic_string(words->word_parts, &argv_string))
				return (free(argv_string.string), NULL);
		}
		else
		{
			if (!expand_word_to_dynamic_string(words->word_parts, &argv_string))
				return (free(argv_string.string), NULL);
		}
		words = words->next;
	}
	argv = convert_dynamic_string_to_str_arr(&argv_string);
	return (argv);
}

bool	expand_words_in_ast(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (true);
	if (node->type == NODE_COMMAND)
	{
		node->command->argv = expand_to_argv(node->command->words, shell);
		if (!node->command->argv)
			return (false);
	}
	if (!expand_words_in_ast(node->left, shell))
		return (false);
	if (!expand_words_in_ast(node->right, shell))
		return (false);
	return (true);
}
