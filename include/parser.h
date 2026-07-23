#ifndef	PARSER_H
#define	PARSER_H

//#include "minishell.h"
#include "tokenizer.h"
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

char			*get_env_value(char *name, char **env);
void			free_words(t_word *words);
void			free_str_arr(char **str_arr);

// parser_free.c
void			free_ast(t_ast_node *node);
void			free_argv(char **argv);
void			free_redirects(t_redirect_node *redirects);
void			free_ast(t_ast_node *node);
void			free_words(t_word *words);

// parser_ast.c
t_node_type		token_type_to_node_type(t_token_type type);
t_ast_node		*create_ast_node(t_node_type type, t_command *command, t_ast_node *left, t_ast_node *right);

// parser_word.c
t_word			*create_word_from_token(t_token **token);
bool			parse_one_word(t_token **current_token, t_word **words_head);

// parser_redirect.c
bool			is_logical(t_token_type type);
t_redirect_node	*parse_redirect(t_token **current_token);
bool			is_redirect(t_token_type type);
void			add_redirect_to_end(t_redirect_node *head, t_redirect_node *new_redirect);

// parser_command.c
t_ast_node		*parse_command(t_token **current_token);

#endif
