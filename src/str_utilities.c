/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:55:36 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/24 15:21:09 by anatoliy         ###   ########.fr       */
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
