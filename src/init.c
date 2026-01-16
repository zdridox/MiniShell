/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:23:22 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/16 22:50:58 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_current_dir_name(char *absolute_pathname)
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
		error_exit("Failed to allocate current_dir_name");
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

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->absolute_pathname = getcwd(NULL, 0);
	if (shell->absolute_pathname == NULL || !*(shell->absolute_pathname))
		error_exit("Falied to get absolute_pathname");
	shell->current_dir_name = init_current_dir_name(shell->absolute_pathname);
	return (shell);
}

