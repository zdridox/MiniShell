/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/06/30 21:42:13 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_new.h"


void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token: '%s', Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

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
		if (isatty(STDIN)) // for testing purposes, we want to read from stdin without readline if it's not a terminal
			input = readline(prompt);
		else
			input = get_next_line(STDIN);
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
		print_tokens(tokens);
		free(input);
		if (!tokens)
			continue ;
		parsed = parse_tokens(tokens);
		if (!parsed)
		{
			free_tokens(tokens);
			continue ;
		}
		if (!expand_words_in_ast(parsed, shell))
		{
			free_ast(parsed);
			free_tokens(tokens);
			continue ;
		}
		execute_parsed(parsed, shell);
		free_ast(parsed);
		free_tokens(tokens);
		if(!isatty(STDIN)) // for testing purposes, we want to exit after one command if we're not in a terminal
		{
			int	exit_code = shell->last_exit_code;
			free_shell(shell);
			return (exit_code);
		}
	}
	return (0);
}
