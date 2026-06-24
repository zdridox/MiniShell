/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:22 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/06/24 14:08:06 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_our_command	*init_our_commands(void)
{
	static t_our_command	our_commands[] = {
		{"cd", &cd_command, false},
		{"exit", &exit_command, false},
		{"env", &env_command, true},
		{"pwd", &pwd_command, true},
		//{"echo", &echo_command},
		//{"export", &export_command},
		//{"unset", &unset_command},
		{NULL, NULL, false}
	};

	return (our_commands);
}

void	init_shell_with_null(t_shell *shell)
{
	shell->env = NULL;
	shell->our_commands = NULL;
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (shell == NULL)
		error_exit("Failed to allocate shell", NULL);
	init_shell_with_null(shell);
	shell->env = copy_arr(envp);
	shell->our_commands = init_our_commands();
	shell->last_exit_code = 0;
	if (shell->env == NULL || shell->our_commands == NULL)
		error_exit("Failed to initialize shell", shell);
	return (shell);
}
