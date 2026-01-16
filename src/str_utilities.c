/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:55:36 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/16 23:05:44 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(const char *str)
{
	write(STDOUT, str, ft_strlen(str));
}

void	ft_putchr(const char c)
{
	write(STDOUT, &c, 1);
}
