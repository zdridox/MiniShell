/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:13:46 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/29 16:18:09 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	match_pattern(char *entry_name, char *pattern);

static bool	handle_wildcard(char *entry_name, char *pattern)
{
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0' || *pattern == '/')
		return (true);
	while (*entry_name)
	{
		if (*entry_name == *pattern || (*pattern == QUOTED_WILDCARD
				&& *entry_name == '*'))
		{
			if (match_pattern(entry_name + 1, pattern + 1))
				return (true);
		}
		entry_name++;
	}
	return (false);
}

static bool	match_pattern(char *entry_name, char *pattern)
{
	if (*pattern == '\0')
		return (*entry_name == '\0');
	if (*pattern == '/' && *entry_name == '\0')
		return (true);
	if (*pattern == '*')
		return (handle_wildcard(entry_name, pattern));
	else if (*pattern == *entry_name || (*pattern == QUOTED_WILDCARD
			&& *entry_name == '*'))
		return (match_pattern(entry_name + 1, pattern + 1));
	return (false);
}

bool	is_valid_match(char *entry_name, char *pattern)
{
	if (*entry_name == '.' && *pattern != '.')
		return (false);
	return (match_pattern(entry_name, pattern));
}
