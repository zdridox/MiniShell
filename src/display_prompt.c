/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:53:50 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/18 17:45:11 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(t_shell *shell)
{
	ft_putstr(GREEN);
	ft_putstr(" ➜ ");
	ft_putstr(RESET);

	ft_putstr(BLUE);
	ft_putstr(shell->current_dir_name);
	ft_putstr(RESET);

	ft_putstr(ORANGE);
	ft_putstr(" ✗");
	ft_putstr(RESET);
}
