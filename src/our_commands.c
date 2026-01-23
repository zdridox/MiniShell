/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:24:53 by maxim             #+#    #+#             */
/*   Updated: 2026/01/22 23:03:00 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command(t_shell *shell, char **args)
{
	char	*old_dir;
	char	*new_dir;
	int		result;

	// free(get_env_pointer("OLDPWD", shell->env));
	old_dir = ft_strdup(get_env_value("PWD", shell->env));
	if (old_dir == NULL)
		return (1);
	set_env_variable("OLDPWD", old_dir, shell->env);
	if (args[1] == NULL)
		new_dir = get_env_value("HOME", shell->env);
	else
		new_dir = args[1];
	result = chdir(new_dir);
	return (result);
}
