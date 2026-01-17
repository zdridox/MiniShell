/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 07:21:03 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/17 07:37:59 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && name[j])
		{
			if (name[j] != env[i][j])
				break ;
			j++;
		}
		if (name[j] == '\0')
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}
