/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:04:20 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/17 07:34:22 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define STDERR 2
# define STDOUT 1
# define GREEN "\033[38;5;121m"
# define BLUE "\033[38;5;87m"
# define ORANGE "\033[38;5;222m"
# define RESET "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct	s_shell
{
	char	*absolute_pathname;
	char	*current_dir_name;
	char	**env;
}				t_shell;

char	**tokenizer(char *input);
t_shell	*init_shell(char **envp);
void	print_current_dir_name(t_shell *shell);
void	error_exit(const char *error_message);
void	display_prompt(t_shell *shell);
void	execute_comand(t_shell *shell, char **tokens);
char	*get_env_value(char *name, char **env);

#endif
