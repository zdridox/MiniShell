#ifndef	TOKENIZER_H
#define	TOKENIZER_H

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	AND,
	OR,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	ERROR,
	END
}				t_token_type;

typedef enum	e_word_part_type
{
	PLAIN,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
}				t_word_part_type;

typedef struct	s_word_part
{
	t_word_part_type	type;
	char				*value;
	struct s_word_part	*next;
}				t_word_part;

typedef struct	s_token
{
	t_token_type	type;
	t_word_part		*word_parts;
	char			*value;
	struct s_token	*next;
}				t_token;

// tokenize_input.c
t_token	*tokenize_input(char *input);

// tokenizer_char_utils.c
bool	is_space(char c);
bool	is_quote(char c);
bool	is_operator(char c);
bool	is_word_end(char c);

// tokenizer_token_utils.c
bool	add_token(t_token **current, t_token_type type, char *value);
bool	add_word_token(char *input, int *i, t_token **current);
bool	add_operator_token(char *input, int *i, t_token **current);

// tokenizer_word_parts.c
bool	add_word_parts(t_token *word_token, char *input, int *i);

// tokenizer_word_length.c
int		get_plain_part_length(char *input, int i);
int		get_quoted_part_length(char *input, int i, char quote_char);

//tokenizer_free.c
void	free_tokens(t_token *tokens);

#endif
