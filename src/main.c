/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/07/23 19:46:20 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_ast_node	*parsed;
	t_token		*tokens;
	char		*input;
	char		*prompt;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		error_exit("Failed to initialize shell", shell);
	while (true)
	{
		prompt = build_prompt(shell);
		if (isatty(STDIN_FILENO)) // for testing purposes, we want to read from stdin without readline if it's not a terminal
			input = readline(prompt);
		else
			input = get_next_line(STDIN_FILENO);
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
		if(!isatty(STDIN_FILENO)) // for testing purposes, we want to exit after one command if we're not in a terminal
		{
			int	exit_code = shell->last_exit_code;
			free_shell(shell);
			return (exit_code);
		}
	}
	return (0);
}
