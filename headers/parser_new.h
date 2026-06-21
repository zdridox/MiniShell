#ifndef	PARSER_NEW_H
#define	PARSER_NEW_H

#include "minishell.h"
#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdlib.h>

# define INITIAL_BUFFER_SIZE 64
# define EQUAL 0

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

typedef struct	s_buffer
{
	char	*data;
	size_t	length;
	size_t	size;
}				t_buffer;

typedef struct	s_word
{
	t_word_part			*word_parts;
	struct s_word		*next;
}				t_word;

typedef struct	s_redirect_node
{
	t_redirect_type			type;
	t_word					*target;
	char					*target_str;
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

char		*get_env_value(char *name, char **env);
void		free_words(t_word *words);
void		free_str_arr(char **str_arr);

#endif
