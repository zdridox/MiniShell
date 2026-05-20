#ifndef	PARSER_NEW_H
#define	PARSER_NEW_H

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

typedef enum	e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}				t_node_type;

typedef enum	e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}				t_redirect_type;

typedef struct	s_word
{
	t_word_part			*word_parts;
	struct s_word		*next;
}				t_word;

typedef struct	s_redirect_node
{
	t_redirect_type			type;
	t_word					*target;
	struct s_redirect_node	*next;
}				t_redirect_node;

typedef struct	s_command
{
	t_word			*words;
	char			**argv;
	t_redirect_node	*redirects;
}				t_command;

typedef struct	s_ast_node
{
	t_node_type			type;
	t_command			*command;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}				t_ast_node;

t_ast_node	*parse_tokens(t_token *tokens);

#endif
