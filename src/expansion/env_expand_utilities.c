/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:28:04 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/28 15:30:22 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	is_valid_env_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_last_exit_status_variable(char *str)
{
	if (!str || !str[0])
		return (false);
	return (str[0] == '?' && !is_valid_env_variable_char(str[1]));
}

int	get_variable_name_length(const char *str)
{
	int	length;

	length = 0;
	while (str[length] && is_valid_env_variable_char(str[length]))
		length++;
	return (length);
}
