/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:04:20 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/24 19:51:44 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define STDERR 2
# define STDOUT 1
# define EQUAL 0
# define CHILD_PROCESS 0
# define GREEN "\033[38;5;121m"
# define BLUE "\033[38;5;87m"
# define ORANGE "\033[38;5;222m"
# define RESET "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_shell	t_shell;

typedef int	(*t_our_command_fn)(t_shell *shell, char **args);

typedef struct	s_our_commands
{
	char	*name;
	t_our_command_fn	function;
}				t_our_commands;

typedef struct	s_shell
{
	char			**env;
	t_our_commands	*our_commands;
}				t_shell;

char	**tokenizer(char *input);
t_shell	*init_shell(char **envp);
void	print_current_dir_name(t_shell *shell);
void	display_prompt(t_shell *shell);
char	*build_prompt(t_shell *shell);
void	execute_comand(char **tokens, t_shell *shell);
char	*get_env_value(char *name, char **env);
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
// TODO: make strjoin with unlimited number of strings
void	free_str_arr(char **str_arr);
int		str_arr_len(char **str_arr);
char	**add_back_str_arr(char **str_arr, char *new_element);
char	**resize_str_arr(char **old_str_arr, int new_size);
char	**copy_arr(char **old_str_arr);
void	print_str_arr(char **str_arr);
void	error_exit(const char *error_message, t_shell *shell);
void	display_error_message(const char *error_message);
void	exit_shell(t_shell *shell);
void	free_shell(t_shell *shell);
char	**get_env_pointer(char *name, char **env);
void	set_env_variable(char *env_name, char *value, char **env);
int		cd_command(t_shell *shell, char **args);
int		exit_command(t_shell *shell, char **args);
int		env_command(t_shell *shell, char **args);
char	*get_current_dir_name(t_shell *shell);

#endif
