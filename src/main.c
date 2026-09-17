/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/08/02 21:58:38 by mzdrodow         ###   ########.fr       */
=======
/*   Updated: 2026/08/05 15:30:15 by mamelnyk         ###   ########.fr       */
>>>>>>> origin/norm_refactoring
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static char	*read_input(t_shell *shell)
{
	char	*input;
	char	*prompt;

	prompt = build_prompt(shell);
	if (isatty(STDIN_FILENO))
		input = readline(prompt);
	else
		input = get_next_line(STDIN_FILENO);
	free(prompt);
	if (!input)
		exit_shell(shell);
	return (input);
}

static void	process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_ast_node	*parsed;

	add_history(input);
	tokens = tokenize_input(input);
	if (!tokens)
		return ;
	parsed = parse_tokens(tokens);
	if (!parsed)
	{
		free_tokens(tokens);
		return ;
	}
	if (!expand_words_in_ast(parsed, shell))
	{
		free_ast(parsed);
		free_tokens(tokens);
		return ;
	}
	execute_parsed(parsed, shell);
	free_ast(parsed);
	free_tokens(tokens);
}

static int	clean_up_get_exit_code(t_shell *shell)
{
	int	exit_code;

	exit_code = shell->last_exit_code;
	free_shell(shell);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	char		*input;

	(void)argc;
	(void)argv;
	init_signals();
	shell = init_shell(envp);
<<<<<<< HEAD
	if (!shell)
		error_exit("Failed to initialize shell", shell);
	shell->shl_varr = var_arr_create();
	shell->env_varr = var_arr_create();
	while (TRUE)
=======
	while (true)
>>>>>>> origin/norm_refactoring
	{
		input = read_input(shell);
		if (check_empty_input(input) == EMPTY)
		{
			free(input);
			continue ;
		}
		process_input(input, shell);
		free(input);
		if (!isatty(STDIN_FILENO))
			return (clean_up_get_exit_code(shell));
	}
	return (0);
}


// need combine of words function
// change how execute commands looks for builtin
// change how eecute commands passes args to command