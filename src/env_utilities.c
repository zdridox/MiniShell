/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 07:21:03 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/24 00:49:04 by mamelnyk         ###   ########.fr       */
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

char	*get_current_dir_name(t_shell *shell)
{
	char	*current_dir_name;
	char	*absolute_pathname;
	int		absolute_pathname_len;
	int		i;

	absolute_pathname = get_env_value("PWD", shell->env);
	if (absolute_pathname == NULL)
		return (NULL);
	i = 0;
	absolute_pathname_len = ft_strlen(absolute_pathname);
	while (absolute_pathname[absolute_pathname_len - i - 1] != '/')
		i++;
	current_dir_name = absolute_pathname + absolute_pathname_len - i;
	return (current_dir_name);
}
