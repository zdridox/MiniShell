#include "../headers/minishell.h"

int export(t_shell *shell, char *var, char *value) {
    if(!shell || !var || !value)
        return (-2);
    if(value == NULL) {
        if(get_shell_var_value(shell->shl_varr, var) == NULL)
            return (-1);
        set_shell_var_value(shell->env_varr, var, get_shell_var_value(shell->shl_varr, var));
        return (0);
    }
    set_shell_var_value(shell->shl_varr, var, value);
    set_shell_var_value(shell->env_varr, var, value);
    return (0);
}