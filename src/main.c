/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/17 07:33:58 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_tokens(char **tokens)
{
	while (*tokens)
	{
		ft_printf("%s\n", *tokens);
		tokens++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	**tokens;
	char	*input;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	printf("%s\n", get_env_value("PATH", shell->env));
	while (TRUE)
	{
		display_prompt(shell);
		input = readline(NULL);
		tokens = tokenizer(input);
		printf("%s\n", input);
		ft_putchar('\n');
		display_tokens(tokens);
		execute_comand(shell, tokens);
	}
	return 0;
}
