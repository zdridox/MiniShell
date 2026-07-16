/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:42:42 by anatoliy          #+#    #+#             */
/*   Updated: 2026/04/17 09:26:27 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_message(const char *error_message)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	free_shell(t_shell *shell)
{
	free_str_arr(shell->env);
	rl_clear_history();
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
