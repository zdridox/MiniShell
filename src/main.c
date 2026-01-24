/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/24 14:21:22 by anatoliy         ###   ########.fr       */
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
		tokens = tokenizer(input);
		free(input);
		execute_comand(tokens, shell);
		free_str_arr(tokens);
	}
	return 0;
}
