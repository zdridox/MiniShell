/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 05:45:34 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/25 05:57:12 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_is_space(input[i]))
			return (NOT_EMPTY);
		i++;
	}
	return (EMPTY);
}
