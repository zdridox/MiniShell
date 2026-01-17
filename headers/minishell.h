/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:04:20 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/17 04:31:59 by anatoliy         ###   ########.fr       */
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
void	ft_putchr(const char c);
void	ft_putstr(const char *str);
t_shell	*init_shell(void);
void	print_current_dir_name(t_shell *shell);
void	error_exit(const char *error_message);
void	display_prompt(t_shell *shell);

#endif
