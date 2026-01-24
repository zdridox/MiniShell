/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:22 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/24 02:07:39 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_our_commands	*init_our_commands(void)
{
	static t_our_commands	our_commands[] = {
		{"cd", &cd_command},
		//{"echo", &echo_command},
		//{"env", &env_command},
		//{"exit", &exit_command},
		//{"export", &export_command},
		//{"pwd", &pwd_command},
		//{"unset", &unset_command},
		{NULL, NULL}
	};
	return (our_commands);
}

void	init_shell_with_null(t_shell *shell)
{
	shell->absolute_pathname = NULL;
	shell->current_dir_name = NULL;
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
	shell->absolute_pathname = getcwd(NULL, 0);
	if (shell->absolute_pathname == NULL || !*(shell->absolute_pathname))
		error_exit("Falied to get absolute_pathname", shell);
	shell->env = envp;
	shell->current_dir_name = get_current_dir_name(shell);
	shell->our_commands = init_our_commands();
	return (shell);
}
