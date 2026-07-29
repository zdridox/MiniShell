/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:18:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/28 17:11:10 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	append_expanded_variable_to_dynamic_string(
		t_dynamic_string *dynamic_string, char *str, int *i, t_shell *shell)
{
	char	*var_value;
	int		var_name_length;
	char	variable_name[MAX_ENV_VARIABLE_NAME_LENGTH + 1];

	(*i)++;
	if (is_last_exit_status_variable(str + *i))
	{
		(*i)++;
		return (append_int_to_dynamic_string(shell->last_exit_code,
				dynamic_string));
	}
	var_name_length = get_variable_name_length(str + *i);
	if (var_name_length > MAX_ENV_VARIABLE_NAME_LENGTH)
		var_name_length = MAX_ENV_VARIABLE_NAME_LENGTH;
	if (var_name_length == 0)
		return (add_char_to_dynamic_string('$', dynamic_string));
	ft_strlcpy(variable_name, str + *i, var_name_length + 1);
	var_value = get_env_value(variable_name, shell->env);
	*i += var_name_length;
	if (!var_value)
		return (true);
	if (!add_n_chars_to_dynamic_string(var_value, ft_strlen(var_value),
			dynamic_string))
		return (false);
	return (true);
}

static char	*expand_environment_variables_in_string(char *str, t_shell *shell)
{
	t_dynamic_string	expanded_string;
	int					i;

	if (!init_dynamic_string(&expanded_string, INITIAL_DYNAMIC_STRING_CAPACITY))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!append_expanded_variable_to_dynamic_string(&expanded_string,
					str, &i, shell))
				return (free(expanded_string.string), NULL);
		}
		else if (!add_char_to_dynamic_string(str[i++], &expanded_string))
			return (free(expanded_string.string), NULL);
	}
	if (!add_char_to_dynamic_string('\0', &expanded_string))
		return (free(expanded_string.string), NULL);
	return (expanded_string.string);
}

static bool	expand_environment_variables_in_word(t_word_part *word_parts,
		t_shell *shell)
{
	char	*expanded_value;

	while (word_parts)
	{
		if ((word_parts->type == PLAIN || word_parts->type == DOUBLE_QUOTED))
		{
			expanded_value = expand_environment_variables_in_string(
					word_parts->value, shell);
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
