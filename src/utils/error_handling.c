/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:42:42 by anatoliy          #+#    #+#             */
/*   Updated: 2026/08/02 20:46:04 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_message(const char *error_message)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	display_error_message_with_context(const char *error_message,
			const char *context)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	if (context)
		ft_putstr_fd((char *)context, STDERR_FILENO);
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
