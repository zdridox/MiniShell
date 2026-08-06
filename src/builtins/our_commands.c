/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:24:53 by maxim             #+#    #+#             */
/*   Updated: 2026/08/06 20:28:59 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_command(t_shell *shell, char **args)
{
	free_argv(args);
	exit_shell(shell);
	return (0);
}

int	env_command(t_shell *shell, char **args)
{
	(void)args;
	print_str_arr(shell->env);
	return (0);
}

int	pwd_command(t_shell *shell, char **args)
{
	(void)args;
	ft_putstr(get_env_value("PWD", shell->env));
	ft_putchar('\n');
	return (0);
}
