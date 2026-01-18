/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:42:42 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/18 21:23:56 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_message(const char *error_message)
{
	ft_putstr_fd("Erorr: ", STDERR);
	ft_putstr_fd((char *)error_message, STDERR);
	ft_putchar_fd('\n', STDERR);
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

void	error_exit(const char *error_message, t_shell *shell)
{
	display_error_message(error_message);
	if (shell)
		free_shell(shell);
	exit(-1);
}
