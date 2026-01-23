/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:22 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/23 20:58:25 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_dir_name(t_shell *shell)
{
	char	*current_dir_name;
	int		absolute_pathname_len;
	int		i;
	int		j;

	i = 0;
	absolute_pathname_len = ft_strlen(absolute_pathname);
	while (absolute_pathname[absolute_pathname_len - i - 1] != '/')
		i++;
	i--;
	current_dir_name = (char *)malloc(i + 2);
	if (current_dir_name == NULL)
		error_exit("Failed to allocate current_dir_name", shell);
		// free shell
	current_dir_name[i + 1] = '\0';
	j = 0;
	while (i >= 0)
	{
		current_dir_name[j] = absolute_pathname[absolute_pathname_len - i - 1];
		i--;
		j++;
	}
	return (current_dir_name);
}

t_our_commands	*init_our_commands(void)
{
	static	t_our_commands	our_commands[] = {
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
	shell->current_dir_name = init_current_dir_name(shell->absolute_pathname, shell);
	shell->our_commands = init_our_commands();
	return (shell);
}
