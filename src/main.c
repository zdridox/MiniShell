/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/06/06 21:07:36 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_new.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_ast_node	*parsed;
	t_token		*tokens;
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
		tokens = tokenize_input(input);
		free(input);
		if (!tokens)
			continue ;
		parsed = parse_tokens(tokens, shell);
		if (!parsed)
		{
			free_tokens(tokens);
			continue ;
		}
		execute_parsed(parsed, shell);
		free_ast(parsed);
		free_tokens(tokens);
	}
	return (0);
}
