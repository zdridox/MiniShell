/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 05:45:34 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/09/14 14:16:42 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_empty_input(char *input)
{
	int	i;

	if (!input)
		return (EMPTY);
	i = 0;
	while (input[i])
	{
		if (!ft_is_space(input[i]))
			return (NOT_EMPTY);
		i++;
	}
	return (EMPTY);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
