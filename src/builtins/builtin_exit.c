/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 21:26:55 by maxim             #+#    #+#             */
/*   Updated: 2026/09/18 21:41:15 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static bool	parse_digits(const char *str, int *i,
				unsigned long long limit, unsigned long long *number)
{
	unsigned int	digit;

	if (!ft_isdigit(str[*i]))
		return (false);
	while (str[*i] && ft_isdigit(str[*i]))
	{
		digit = str[*i] - '0';
		if (*number > (limit - digit) / 10)
			return (false);
		*number = *number * 10 + digit;
		(*i)++;
	}
	return (true);
}

static bool	parse_exit_code(const char *str, int *exit_code)
{
	unsigned long long	number;
	unsigned long long	limit;
	int					sign;
	int					i;

	if (!str || !exit_code)
		return (false);
	i = 0;
	number = 0;
	sign = parse_sign(str, &i);
	if (sign > 0)
		limit = (unsigned long long)LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MIN;
	if (!parse_digits(str, &i, limit, &number))
		return (false);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (false);
	*exit_code = number % 256;
	if (sign < 0 && *exit_code != 0)
		*exit_code = 256 - *exit_code;
	return (true);
}

int	exit_command(t_shell *shell, char **args)
{
	int	exit_code;

	if (!args[1])
	{
		shell->should_exit = true;
		return (shell->last_exit_code);
	}
	if (!parse_exit_code(args[1], &exit_code))
	{
		display_error_message_with_context(
			"exit: numeric argument required: ", args[1]);
		shell->should_exit = true;
		return (255);
	}
	if (args[2])
	{
		display_error_message_with_context("exit: too many arguments", args[1]);
		return (1);
	}
	shell->should_exit = true;
	return ((unsigned char)exit_code);
}
