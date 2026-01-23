/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 07:21:03 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/22 22:59:46 by maxim            ###   ########.fr       */
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

void	set_env_variable(char *env_name, char *value, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env_name[j])
		{
			if (env_name[j] != env[i][j])
				break ;
			j++;
		}
		if (env_name[j] == '\0')
		{
			//free(env[i]);
			env[i] = ft_strjoin_three(env_name, "=", value);
			return ;
		}
		i++;
	}
}

char	**get_env_pointer(char *name, char **env)
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
			return (&env[i]);
		i++;
	}
	return (NULL);
}
