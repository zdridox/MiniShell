/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   export.c                                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/25 22:03:36 by username         #+#    #+#              */
/*   Updated: 2026/09/25 22:05:15 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int export(t_shell *shell, char *var, char *value) {
//     if(!shell || !var || !value)
//         return (-2);
//     if(value == NULL) {
//         if(get_shell_var_value(shell->shl_varr, var) == NULL)
//             return (-1);
//         set_shell_var_value(shell->env_varr, var,
// get_shell_var_value(shell->shl_varr, var));
//         return (0);
//     }
//     //set_shell_var_value(shell->shl_varr, var, value);
//     set_shell_var_value(shell->env_varr, var, value);
//     return (0);
// }

// int unset(t_shell *shell, char *var) {
//     if(!shell || !var)
//         return (-2);
//     //remove_shell_var(shell->shl_varr, var);
//     remove_shell_var(shell->env_varr, var);
//     return (0);
// }

char **alpha_sort_strarr(char **arr)
{
	int i;
	int j;
	char *tmp;
	char **copy;

	copy = copy_arr(arr);
	i = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[j + 1])
		{
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
			{
				tmp = copy[j];
				copy[j] = copy[j + 1];
				copy[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (copy);
}

int export_f(t_shell *shell, char **argv)
{
	char **args;
	size_t i;

	i = 0;
	while (argv[++i])
	{
		args = split_once(argv[i], '=');
		if (validate_svar(args[0]) != 1)
			return (free_str_arr(args), -1);
		if (!ft_strcmp(args[1], "NO="))
		{
			if(get_shell_var_value(shell->env_varr, args[0]) == NULL)
				set_shell_var_value(shell->env_varr, args[0], "", shell);
		}
		else
		{
			if (args[1] == NULL)
				set_shell_var_value(shell->env_varr, args[0], "", shell);
			else
				set_shell_var_value(shell->env_varr, args[0], args[1], shell);
		}
		free_str_arr(args);
	}
	return (0);
}

int export_print_f(t_shell *shell, char **argv)
{
	char **sorted;

	(void)argv;
	sorted = alpha_sort_strarr(shell->env_varr->var_arr);
	print_str_arr(sorted);
	free_str_arr(sorted);
	return (0);
}

int unset_f(t_shell *shell, char **argv)
{
	size_t i;

	if (argv == NULL || argv[0] == NULL)
		return (-1);
	i = 0;
	while (argv[++i])
		remove_shell_var(shell->env_varr, argv[i]);
	return (0);
}
