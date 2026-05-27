/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/05/27 21:46:56 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	**tokens;
	char	*input;
	char	*prompt;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		error_exit("Failed to initialize shell", shell);
	while (TRUE)
	{
		prompt = build_prompt(shell);
		input = readline(prompt);
		free(prompt);
		if (!input)
			exit_shell(shell);
		if (check_empty_input(input) == EMPTY)
		{
			free(input);
			continue ;
		}
		add_history(input);
		//tokens = ft_split(input, ' ');
		tokens = tokenizer(input);
		free(input);
		execute_comand(tokens, shell);
		free_str_arr(tokens);
	}
	return (0);
}
