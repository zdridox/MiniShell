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

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

#endif
