/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:22 by mamelnyk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/05/27 21:30:00 by mzdrodow         ###   ########.fr       */
=======
/*   Updated: 2026/05/28 12:48:56 by anatoliy         ###   ########.fr       */
>>>>>>> new_execution
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_our_commands	*init_our_commands(void)
{
	static t_our_commands	our_commands[] = {
		{"cd", &cd_command},
		{"exit", &exit_command},
		{"env", &env_command},
		{"pwd", &pwd_command},
		{"echo", &echo_command},
		//{"export", &export_command},
		//{"unset", &unset_command},
		{NULL, NULL}
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
