#include "minishell.h"

// int export(t_shell *shell, char *var, char *value) {
//     if(!shell || !var || !value)
//         return (-2);
//     if(value == NULL) {
//         if(get_shell_var_value(shell->shl_varr, var) == NULL)
//             return (-1);
//         set_shell_var_value(shell->env_varr, var, get_shell_var_value(shell->shl_varr, var));
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

char **alpha_sort_strarr(char **arr) {
    int		i;
    int		j;
    char	*tmp;
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

int export_f(t_shell *shell, char **argv) {
    char **args;

    args = split_once(argv[1], '=');
    if(validate_svar(args[0]) != 1)
        return (-1);
    if(args[1] == NULL)
        set_shell_var_value(shell->env_varr, args[0], "", shell);
    else
        set_shell_var_value(shell->env_varr, args[0], args[1], shell);
    free_str_arr(args);
    return (0);
}

int export_print_f(t_shell *shell, char **argv) {
    char **sorted;

    (void)argv;
    sorted = alpha_sort_strarr(shell->env_varr->var_arr);
    print_str_arr(sorted);
    free_str_arr(sorted);
    return (0);
}

int unset_f(t_shell *shell, char **argv) {
    if(argv[0] == NULL || argv[1] == NULL)
        return (-1);
    remove_shell_var(shell->env_varr, argv[1]);
    return (0);
}