/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:26:23 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/17 14:29:26 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_bin_path(t_shell *shell)
{
	char	**path;
	char	*bin_path;

}

void	execute_comand(t_shell *shell, char **tokens)
{
	pid_t	pid;
	char	*argv[] = {"./a.out", NULL};

	(void)shell;
	(void)tokens;
	pid = fork();
	if (pid < 0)
		error_exit("Can make new process");
		// free shell
	execve("./a.out", argv, NULL);
	wait(NULL);
}
