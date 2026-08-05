/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:04:20 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/05 15:33:58 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN_FILENO	0
# define STDOUT_FILENO	1
# define STDERR_FILENO	2

# define SUCCESS	0
# define ERROR		1

# define EQUAL			0
# define EMPTY			0
# define NOT_EMPTY		1
# define EXIST			0
# define CHILD_PROCESS	0

# define MAX_ENV_VARIABLE_NAME_LENGTH	256

# define GREEN	"\001\033[38;5;121m\002"
# define BLUE	"\001\033[38;5;87m\002"
# define ORANGE	"\001\033[38;5;222m\002"
# define PURPLE	"\001\033[38;5;135m\002"
# define PINK	"\001\033[38;5;198m\002"
# define RESET	"\001\033[0m\002"

# include <stdbool.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "parser.h"
# include "tokenizer.h"

typedef struct s_shell			t_shell;
typedef struct s_ast_node		t_ast_node;

typedef int						(*t_our_command_fn)(t_shell *shell,
								char **args);

typedef struct s_our_command
{
	char				*name;
	t_our_command_fn	function;
	bool				run_in_child_process;
}	t_our_command;

typedef struct s_shell
{
	int					last_exit_code;
	char				**env;
	t_our_command		*our_commands;
}	t_shell;

typedef enum e_exec_status
{
	EXEC_SUCCESS,
	EXEC_FAILURE,
	EXEC_EXIT
}	t_exec_status;

typedef struct s_cmd_io
{
	int	input_fd;
	int	output_fd;
}	t_cmd_io;

t_shell		*init_shell(char **envp);

void		print_current_dir_name(t_shell *shell);
void		display_prompt(t_shell *shell);
char		*build_prompt(t_shell *shell);

void		execute_comand(char **tokens, t_shell *shell);
void		execute_parsed(t_ast_node *ast, t_shell *shell);

char		*get_env_value(char *name, char **env);
char		**get_env_pointer(char *name, char **env);
bool		set_env_variable(char *env_name, char *value, char **env);

char		*ft_strjoin_three(const char *s1, const char *s2,
				const char *s3);

int			ft_is_space(char c);

void		free_str_arr(char **str_arr);
int			str_arr_len(char **str_arr);
char		**add_back_str_arr(char **str_arr, char *new_element);
char		**resize_str_arr(char **old_str_arr, int new_size);
char		**copy_arr(char **old_str_arr);
void		print_str_arr(char **str_arr);

void		error_exit(const char *error_message, t_shell *shell);
void		display_error_message_with_context(const char *error_message,
				const char *context);
void		display_error_message(const char *error_message);

void		exit_shell(t_shell *shell);
void		free_shell(t_shell *shell);

// builtin_cd.c
int			cd_command(t_shell *shell, char **args);
int			pwd_command(t_shell *shell, char **args);
int			exit_command(t_shell *shell, char **args);
int			env_command(t_shell *shell, char **args);

char		*get_current_dir_name(t_shell *shell);
// shell_utilities.c
bool		check_empty_input(char *input);
void		sigint_handler(int signum);

bool		write_heredoc_to_file(char *delimiter, char *file_path);
char		*generate_temp_file_path(void *seed);

// ast_expand.c
void		free_ast(t_ast_node *node);
bool		expand_words_in_ast(t_ast_node *node, t_shell *shell);

// exec_ast.c
void		execute_parsed(t_ast_node *ast, t_shell *shell);

t_ast_node	*parse_tokens(t_token *tokens);

#endif
