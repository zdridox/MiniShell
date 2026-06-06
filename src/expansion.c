/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:18:34 by anatoliy          #+#    #+#             */
/*   Updated: 2026/06/05 12:24:34 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_new.h"

bool	init_buffer(t_buffer *buffer)
{
	buffer->data = malloc(INITIAL_BUFFER_SIZE);
	if (!buffer->data)
		return (false);
	buffer->size = INITIAL_BUFFER_SIZE;
	buffer->length = 0;
	return (true);
}

bool	resize_buffer(t_buffer *buffer)
{
	char	*new_data;
	size_t	new_size;

	new_size = buffer->size * 2;
	new_data = malloc(new_size);
	if (!new_data)
		return (free(buffer->data), false);
	ft_memcpy(new_data, buffer->data, buffer->length);
	free(buffer->data);
	buffer->data = new_data;
	buffer->size = new_size;
	return (true);
}

bool	append_char_to_buffer(t_buffer *buffer, char c)
{
	if (buffer->length + 1 >= buffer->size)
	{
		if (!resize_buffer(buffer))
			return (false);
	}
	buffer->data[buffer->length] = c;
	buffer->length++;
	return (true);
}

int	get_variable_name_length(const char *str)
{
	int length = 0;

	while (str[length] && (ft_isalnum(str[length]) || str[length] == '_'))
		length++;
	return (length);
}

void	skip_variable_name(const char *str, int *i)
{
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
}

bool	append_expanded_variable_to_buffer(t_buffer *buffer, char *str, int *i, char **env)
{
	char	*var_value;
	int		var_name_length;

	(*i)++;
	//TODO first check if it's a $?
	var_name_length = get_variable_name_length(str + *i);
	if (var_name_length == 0)
		return (append_char_to_buffer(buffer, '$'));
	var_value = get_env_value(str + *i, env);
	if (!var_value)
	{
		skip_variable_name(str, i);
		return (true);
	}
	while (*var_value)
	{
		if (!append_char_to_buffer(buffer, *var_value))
			return (false);
		var_value++;
	}
	skip_variable_name(str, i);
	return (true);
}

char	*expand_environment_variables_in_string(char *str, char **env)
{
	t_buffer	buffer;
	int			i;

	if (!init_buffer(&buffer))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!append_expanded_variable_to_buffer(&buffer, str, &i, env))
				return (free(buffer.data), NULL);
		}
		else
		{
			if (!append_char_to_buffer(&buffer, str[i]))
				return (free(buffer.data), NULL);
			i++;
		}
	}
	if (!append_char_to_buffer(&buffer, '\0'))
		return (free(buffer.data), NULL);
	return (buffer.data);
}

bool	expand_environment_variables_in_word(t_word_part *word_parts, char **env)
{
	char	*expanded_value;

	while (word_parts)
	{
		if (word_parts->type == PLAIN || word_parts->type == DOUBLE_QUOTED)
		{
			expanded_value = expand_environment_variables_in_string(word_parts->value, env);
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

bool	expand_environment_variables(t_word *words, char **env)
{
	t_word	*current_word;

	current_word = words;
	while (current_word)
	{
		if (!expand_environment_variables_in_word(current_word->word_parts, env))
			return (free_words(words), false);
		current_word = current_word->next;
	}
	return (true);
}

bool	expanad_wildcards(t_word *words)
{
	(void)words;
	return (true);
}

size_t	calculate_converted_length(t_word_part *word_parts)
{
	size_t	length = 0;

	while (word_parts)
	{
		length += ft_strlen(word_parts->value);
		word_parts = word_parts->next;
	}
	return (length);
}

void	append_word_part_to_buffer(char *buffer, int *index, const char *str)
{
	int	str_index;

	str_index = 0;
	while (str[str_index])
	{
		buffer[*index] = str[str_index];
		(*index)++;
		str_index++;
	}
	buffer[*index] = '\0';
}

char	*convert_word_to_string(t_word_part *word_parts)
{
	char		*converted_str;
	size_t		converted_length;
	int			i;

	converted_length = calculate_converted_length(word_parts);
	converted_str = malloc(converted_length + 1);
	if (!converted_str)
		return (NULL);
	i = 0;
	while (word_parts)
	{
		append_word_part_to_buffer(converted_str, &i, word_parts->value);
		word_parts = word_parts->next;
	}
	return (converted_str);
}

int	count_words(t_word *words)
{
	int	word_count;

	word_count = 0;
	while (words)
	{
		word_count++;
		words = words->next;
	}
	return (word_count);
}

char	**convert_words_to_argv(t_word *words)
{
	char	**argv;
	int		str_count;
	int		i;

	str_count = count_words(words);
	argv = malloc(sizeof(char *) * (str_count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (words)
	{
		argv[i] = convert_word_to_string(words->word_parts);
		if (!argv[i])
		{
			free_str_arr(argv);
			return (NULL);
		}
		i++;
		words = words->next;
	}
	argv[i] = NULL;
	return (argv);
}

char	**expand_to_argv(t_word *words, char **env)
{
	char	**argv;

	if (!words)
		return (NULL);
	if (!expand_environment_variables(words, env))
		return (NULL);
	if (!expanad_wildcards(words))
		return (NULL);
	argv = convert_words_to_argv(words);
	return (argv);
}

bool	expand_words_in_ast(t_ast_node *node, char **env)
{
	if (!node)
		return (true);
	if (node->type == NODE_COMMAND)
	{
		node->command->argv = expand_to_argv(node->command->words, env);
		if (!node->command->argv)
			return (false);
	}
	if (!expand_words_in_ast(node->left, env))
		return (false);
	if (!expand_words_in_ast(node->right, env))
		return (false);
	return (true);
}

/*
bool ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

t_word_part	*create_word_part_from_string(const char *str)
{
	t_word_part	*word_part;
	int			i;

	word_part = malloc(sizeof(t_word_part));
	if (!word_part)
		return (NULL);
	word_part->type = PLAIN;
	word_part->value = NULL;
	word_part->next = NULL;
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	word_part->value = ft_substr(str, 0, i);
	if (!word_part->value)
		return (free(word_part), NULL);
	return (word_part);
}

t_word	*create_word_list_from_string(const char *str)
{
	t_word	*word_list;
	t_word	*current_word;
	int		i;

	word_list = NULL;
	current_word = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (!current_word)
		{
			current_word = malloc(sizeof(t_word));
			if (!current_word)
				return (free_words(word_list), NULL);
			current_word->word_parts = create_word_part_from_string(str + i);
			current_word->next = NULL;
			word_list = current_word;
		}
		else
		{
			current_word->next = malloc(sizeof(t_word));
			if (!current_word->next)
				return (free_words(word_list), NULL);
			current_word = current_word->next;
			current_word->word_parts = create_word_part_from_string(str + i);
			current_word->next = NULL;
		}
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (word_list);
}

// test and debug expansion functions
int	main(void)
{
	char	*env[] = {
		"USER=anatoliy",
		"HOME=/home/anatoliy",
		"PATH=/usr/bin:/bin",
		NULL
	};
	char	*input = "echo $USER $HOME$PATH";
	char	**argv;

	argv = expand_to_argv(create_word_list_from_string(input), env);
	if (argv)
	{
		printf("Original input: '%s'\n", input);
		printf("Expanded argv:\n");
		for (int i = 0; argv[i]; i++)
			printf("argv[%d]: '%s'\n", i, argv[i]);
		free_str_arr(argv);
	}
	return (0);
}
*/
