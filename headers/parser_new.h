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

typedef struct	s_word_part
{
	t_word_part			*word_parts;
	struct s_word_part	*next;
}				t_word_part;

typedef struct	s_ast_node
{
	t_node_type			type;
	t_command			*command;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}				t_ast_node;

typedef struct	s_redirect
{
	t_redirect_type		type;
	t_word				*target;
	struct s_redirect	*next;
}				t_redirect;

typedef struct	s_command
{
	t_word				*words;
	t_redirect			*redirects;
}				t_command;

#endif
