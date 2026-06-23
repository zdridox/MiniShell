#include "../headers/minishell.h"

void	add_shell_var(t_var_arr **varr, char *full_var)
{
}

void	remove_shell_var(t_var_arr **varr, char *var_name)
{
}

void	set_shell_var_value(t_var_arr *varr, char *var_name, char *value)
{
}

char	*get_shell_var_value(t_var_arr *varr, char *var_name)
{
    int i;

    i = 0;
    while (i < varr->size)
    {
        if(!ft_strcmp(get_name_from_full_var(varr->var_arr[i]), var_name))
            break;
        ++i;
    }
    return (get_value_from_full_var(varr->var_arr[i]));
}

char	*get_name_from_full_var(char *var)
{
    char *name;
    int i;

    i = 0;
    while (var[i] != '=')
        ++i;
    name = malloc(i + 1);
    ft_memcpy(name, var, i);
    name[i] = 0;
    return (name);
}

char	*get_value_from_full_var(char *var)
{
    char *value;
    int i;
    int eqs_index;

    i = 0;
    while (var[i] != 0)
    {
        if(var[i] == '=')
            eqs_index = i;
        ++i;
    }
    value = malloc((i - eqs_index));
    ft_memcpy(value, var + eqs_index, ((i - eqs_index) - 1));
    value[(i - eqs_index) - 1] = 0;
}
