/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:24:53 by maxim             #+#    #+#             */
/*   Updated: 2026/09/18 21:30:31 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int echo_command(t_shell *shell, char **argv) {
	int nl_flag;
	int i;

	(void)shell;
	if(!ft_strcmp("-n", argv[1]))
		nl_flag = 1;
	else
		nl_flag = 0;
	
	i = 0 + nl_flag;
	while (argv[++i])
	{
		if(argv[i + 1] == NULL)
			ft_printf("%s", argv[i]);
		else
			ft_printf("%s ", argv[i]);
	}
	if(nl_flag == 0)
		ft_printf("\n");
	return (0);
}
