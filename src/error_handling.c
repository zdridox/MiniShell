/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:42:42 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/17 20:53:54 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *error_message)
{
	write(STDERR, "Erorr: ", 6);
	write(STDERR, error_message, ft_strlen(error_message));
	write(STDERR, "\n", 1);
	exit(-1);
}

void	free_shell(t_shell *shell)
{
	free_str_arr(shell->env);
	free(shell->absolute_pathname);
	free(shell->current_dir_name);
	free(shell);
}

void	exit_shell(t_shell *shell)
{
	free_shell(shell);
	exit(0);
}
