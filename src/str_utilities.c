/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:55:36 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/26 03:59:38 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (temp == NULL)
		return (NULL);
	result = ft_strjoin(temp, s3);
	if (result == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (result);
}

char	*ft_strjoin_many(int count, ...)
{
	va_list	args;
	char	*result;
	char	*current;
	int		i;
	
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		current = va_arg(args, char *);
		if (!current)
			return (va_end(args), NULL);
		if (i == 0)
		{
			result = ft_strdup(current);
			if (!result)
				return (va_end(args), NULL);
			i++;
			continue ;
		}
		result = ft_strjoin(result, current);
		if (!result)
			return (va_end(args), NULL);
	}
	va_end(args);
	return (result);
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (TRUE);
	return (FALSE);
}
