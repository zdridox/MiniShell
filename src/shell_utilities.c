/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:52:59 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/16 22:51:11 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_current_dir_name(t_shell *shell)
{
	write(STDOUT, shell->current_dir_name, ft_strlen(shell->current_dir_name));
	write(STDOUT, "\n", 1);
}
