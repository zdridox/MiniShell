#include "../headers/minishell.h"

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

int export_f(t_shell *shell, char **argv) {
    char **args;

    args = ft_split(argv[1], "=");
    if(args == NULL || args[0] == NULL|| args[1] == NULL)
        return (-1);
    if(args[2] == NULL)
        set_shell_var_value(shell->env_varr, args[1], "");
    else
        set_shell_var_value(shell->env_varr, args[1], args[2]);
    return (0);
}

int unset_f(t_shell *shell, char **argv) {
    if(argv[0] == NULL || argv[1] == NULL)
        return (-1);
    remove_shell_var(shell->env_varr, argv[1]);
    return (0);
}