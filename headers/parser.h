#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdlib.h>

typedef enum s_flag_type
{
	OVERWRITE,
	APPEND,
	READ_FROM_FILE,
	HEREDOC
}						t_flag_type;

typedef enum s_node_type
{
	FIRST,
	PIPE,
	AND,
	OR
}						t_node_type;

typedef struct s_flag_node
{
	t_flag_type			flag;
	char				*flag_arg;
	struct s_flag_node	*next;
}						t_flag_node;

typedef struct s_cmd_node
{
	t_node_type			type;
	t_flag_node			*flags;
	char				**argv;
	struct s_cmd_node	*next;
}						t_cmd_node;

char					**tokenizer(char *input);
void					cmd_add_back(t_cmd_node *head, t_cmd_node *node);
void					flag_add_back(t_flag_node *head, t_flag_node *node);
char					**resize_str_arr(char **old_str_arr, int new_size);
int						str_arr_len(char **str_arr);
void					print_str_arr(char **str_arr);
void					free_str_arr(char **str_arr);
void					free_parsed(t_cmd_node *parsed);

#endif
