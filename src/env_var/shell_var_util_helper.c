/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   shell_var_util_helper.c                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/25 22:05:29 by username         #+#    #+#              */
/*   Updated: 2026/09/25 22:05:30 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_name_cmp(char *var_name, char *full_var)
{
	size_t	i;

	if (!var_name || !full_var)
		return (-1);
	i = 0;
	while (var_name[i] && full_var[i] != '=')
	{
		if (var_name[i] != full_var[i])
			return (var_name[i] - full_var[i]);
		i++;
	}
	if (var_name[i] == '\0' && full_var[i] == '=')
		return (0);
	return (1);
}

int	fvar_to_fvar_name_cmp(char *full_var1, char *full_var2)
{
	size_t	i;

	if (!full_var1 || !full_var2)
		return (-1);
	i = 0;
	while (full_var1[i] && full_var2[i])
	{
		if (full_var1[i] != full_var2[i])
			return (full_var1[i] - full_var2[i]);
		if (full_var1[i] == '=' && full_var2[i] == '=')
			return (0);
		++i;
	}
	return (1);
}
