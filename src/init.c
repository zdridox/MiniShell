/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:22 by mamelnyk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/06/06 21:12:18 by mzdrodow         ###   ########.fr       */
=======
/*   Updated: 2026/07/27 17:15:28 by mamelnyk         ###   ########.fr       */
>>>>>>> origin/norm_refactoring
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_our_command	*init_our_commands(void)
{
<<<<<<< HEAD
	static t_our_commands	our_commands[] = {
		{"cd", &cd_command},
		{"exit", &exit_command},
		{"env", &env_command},
		{"pwd", &pwd_command},
		{"echo", &echo_command},
=======
	static t_our_command	our_commands[]
		= {{"cd", &cd_command, false},
	{"exit", &exit_command, false},
	{"env", &env_command, true},
	{"pwd", &pwd_command, true},
		//{"echo", &echo_command},
>>>>>>> origin/norm_refactoring
		//{"export", &export_command},
		//{"unset", &unset_command},
	{NULL, NULL, false}};

	return (our_commands);
}

static void	init_shell_with_null(t_shell *shell)
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
	if (shell->env == NULL)
		error_exit("Failed to copy environment variables", shell);
	shell->our_commands = init_our_commands();
	shell->last_exit_code = 0;
	if (shell->env == NULL || shell->our_commands == NULL)
		error_exit("Failed to initialize shell", shell);
	return (shell);
}
