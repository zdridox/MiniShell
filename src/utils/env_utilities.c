/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 07:21:03 by anatoliy          #+#    #+#             */
/*   Updated: 2026/08/09 19:01:42 by mamelnyk         ###   ########.fr       */
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

static bool	is_env_name_equal(char *env_name, char *env_variable)
{
	int	i;

	i = 0;
	while (env_name[i] && env_variable[i])
	{
		if (env_name[i] != env_variable[i])
			return (false);
		i++;
	}
	if (env_name[i] == '\0' && env_variable[i] == '=')
		return (true);
	return (false);
}

bool	set_env_variable(char *env_name, char *value, char **env)
{
	int	i;

	if (!env_name || !value || !env)
		return (false);
	i = 0;
	while (env[i])
	{
		if (is_env_name_equal(env_name, env[i]))
		{
			free(env[i]);
			env[i] = ft_strjoin_three(env_name, "=", value);
			if (!env[i])
				return (false);
			else
				return (true);
		}
		i++;
	}
	return (true);
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
	if (!absolute_pathname)
		return (NULL);
	if (ft_strcmp(absolute_pathname, "/") == 0)
		return (absolute_pathname);
	absolute_pathname_len = ft_strlen(absolute_pathname);
	i = 0;
	while (absolute_pathname[absolute_pathname_len - i - 1] != '/')
		i++;
	current_dir_name = absolute_pathname + absolute_pathname_len - i;
	return (current_dir_name);
}
