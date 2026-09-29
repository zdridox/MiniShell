/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   svar_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 22:41:47 by mzdrodow          #+#    #+#             */
/*   Updated: 2026/09/25 22:41:48 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strchraindex(char *str, const char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				return (i);
			++j;
		}
		++i;
	}
	return (-1);
}

int	validate_svar_name(const char *inc, char *name)
{
	const char	digits[] = "0123456789";

	if (strchraindex(name, digits) == 0)
		return (0);
	if (strchraindex(name, inc) != -1)
		return (0);
	return (1);
}

int	validate_svar(char *name)
{
	int			res;
	static char	illegal_name_chars[38] = {' ', '\t', '\n', '\r', '\v', '\f',
		'-', '+', '.', ',', '!', '@', '#', '$', '%', '^', '&', '*', '(',
		')', '[', ']', '{', '}', '|', '\\', '/', '=', ':', ';', '\'', '"',
		'<', '>', '?', '`', '~', 0};

	res = 0;
	res += validate_svar_name(illegal_name_chars, name);
	if (res != 1)
		return (0);
	return (1);
}
