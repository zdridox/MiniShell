/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:57:40 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/01/17 04:40:52 by anatoliy         ###   ########.fr       */
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

int	main(void)
{
	t_shell	*shell;
	char	**tokens;
	char	*input;

	shell = init_shell();
	while (TRUE)
	{
		display_prompt(shell);
		input = readline(NULL);
		tokens = tokenizer(input);
		printf("%s\n", input);
		ft_putchr('\n');
		display_tokens(tokens);
	}
	return 0;
}
