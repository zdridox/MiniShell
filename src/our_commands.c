/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:24:53 by maxim             #+#    #+#             */
/*   Updated: 2026/05/27 22:12:31 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command(t_shell *shell, char **args)
{
	char	*old_dir;
	char	*new_dir;
	int		result;

	if (str_arr_len(args) >= 3)
	{
		display_error_message("cd: too many arguments");
		return (1);
	}
	old_dir = ft_strdup(get_env_value("PWD", shell->env));
	if (!old_dir)
		return (1);
	// TODO make makro for error codes
	set_env_variable("OLDPWD", old_dir, shell->env);
	free(old_dir);
	if (!args[1] || ft_strcmp(args[1], "~") == EQUAL)
		new_dir = get_env_value("HOME", shell->env);
	else
		new_dir = args[1];
	result = chdir(new_dir);
	new_dir = getcwd(NULL, 0);
	if (result != 0)
	{
		display_error_message("cd: no such file or directory");
		return (1);
	}
	set_env_variable("PWD", new_dir, shell->env);
	free(new_dir);
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
	int	exit_code;

	(void)args;
	exit_code = 0;
	print_str_arr(shell->env);
	return (exit_code);
}

int	pwd_command(t_shell *shell, char **args)
{
	int	exit_code;

	(void)args;
	exit_code = 0;
	ft_putstr(get_env_value("PWD", shell->env));
	ft_putchar('\n');
	return (exit_code);
}

int	echo_command(t_shell *shell, char **args)
{
	int		exit_code;
	int		nl_flag;
	int		i;
	int		len;
	char	*trimmed;

	(void)shell;
	i = 1;
	exit_code = 0;
	nl_flag = 0;
	while (args[i])
	{
		if (i == 1 && ft_strcmp(args[1], "-n") == EQUAL)
		{
			nl_flag = 1;
			++i;
			continue ;
		}
		if (args[i][0] == '"' || args[i][0] == '\'')
		{
			len = ft_strlen(args[i]);
			trimmed = malloc(len - 1);
			ft_memcpy(trimmed, args[i] + 1, len - 2);
			trimmed[len - 2] = 0;
			ft_printf("%s", trimmed);
			free(trimmed);
		} else {
			ft_printf("%s", args[i]);
		}
		if (args[i + 1])
			ft_putchar(' ');
		++i;
	}
	if (nl_flag == 0)
		ft_putchar('\n');
	return (exit_code);
}
