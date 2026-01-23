/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:53:50 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/24 00:45:20 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_prompt(t_shell *shell)
{
	char	*prompt;
	char	*part1;
	char	*part2;
	char	*part3;

	part1 = ft_strjoin(GREEN, " ➜ ");
	part2 = ft_strjoin(BLUE, get_current_dir_name(shell));
	part3 = ft_strjoin_three(ORANGE, " ✗ ", RESET);
	prompt = ft_strjoin_three(part1, part2, part3);
	free(part1);
	free(part2);
	free(part3);
	return (prompt);
}

