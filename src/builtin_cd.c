/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:44:28 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/02 18:44:52 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_target_directory(t_shell *shell, char **args)
{
	char	*target_dir;

	if (!args[1] || ft_strcmp(args[1], "~") == EQUAL)
	{
		target_dir = get_env_value("HOME", shell->env);
		if (!target_dir || !*target_dir)
			display_error_message("cd: HOME not set");
		return (target_dir);
	}
	return (args[1]);
}

static bool	update_environment_variables(t_shell *shell)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = get_env_value("PWD", shell->env);
	if (!old_dir)
		return (display_error_message("cd: PWD not set"), false);
	if (!set_env_variable("OLDPWD", old_dir, shell->env))
		return (display_error_message("cd: failed to set OLDPWD"), false);
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
		return (display_error_message("cd: failed to get current directory"),
			false);
	if (!set_env_variable("PWD", new_dir, shell->env))
	{
		free(new_dir);
		return (display_error_message("cd: failed to set PWD"), false);
	}
	free(new_dir);
	return (true);
}

int	cd_command(t_shell *shell, char **args)
{
	char	*target_dir;

	if (str_arr_len(args) >= 3)
		return (display_error_message("cd: too many arguments"), 1);
	target_dir = resolve_target_directory(shell, args);
	if (!target_dir)
		return (1);
	if (chdir(target_dir))
		return (display_error_message("cd: no such file or directory"), 1);
	if (!update_environment_variables(shell))
		return (1);
	return (0);
}
