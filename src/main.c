/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/04/07 15:22:47 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_cmd_node	*parsed;
	char		**tokens;
	char		*input;
	char		*prompt;

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
		tokens = tokenizer(input);
		parsed = parse_tokens(tokens);
		free(input);
		execute_sequence_of_commands(parsed, shell);
		free_parsed(parsed);
		free_str_arr(tokens);
	}
	return (0);
}
