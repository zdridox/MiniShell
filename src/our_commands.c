/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:24:53 by maxim             #+#    #+#             */
/*   Updated: 2026/01/24 19:52:13 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command(t_shell *shell, char **args)
{
	char	*old_dir;
	char	*new_dir;
	int		result;

	// free(get_env_pointer("OLDPWD", shell->env));
	if (str_arr_len(args) >= 3)
		display_error_message("cd: too many arguments");
	old_dir = ft_strdup(get_env_value("PWD", shell->env));
	if (old_dir == NULL)
		return (1);
		// TODO make makro for error codes
	set_env_variable("OLDPWD", old_dir, shell->env);
	if (args[1] == NULL || ft_strcmp(args[1], "~") == EQUAL)
		new_dir = get_env_value("HOME", shell->env);
	else
		new_dir = args[1];
	result = chdir(new_dir);
	set_env_variable("PWD", getcwd(NULL, 0), shell->env);
	return (result);
}

int	exit_command(t_shell *shell, char **args)
{
	int	exit_code;

	exit_code = 0;
	free_str_arr(args);
	exit_shell(shell);
	return (exit_code);
}

int	env_command(t_shell *shell, char **args)
{
	int exit_code;;

	(void)args;
	exit_code = 0;
	print_str_arr(shell->env);
	return (exit_code);
}
