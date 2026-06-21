#include "../headers/minishell.h"

void	add_shell_var(char **svp, char *full_var)
{
    // remember input is trimmed so if creating an empty var input end right
    // after the null terminator
}

void	remove_shell_var(char **svp, char *var_name)
{
}

void	set_shell_var_value(char **svp, char *var_name, char *value)
{
}

char	*get_shell_var_value(char **svp, char *var_name)
{
}

t_var_arr *var_arr_create() {
    t_var_arr *varr;

    varr = malloc(sizeof(t_var_arr));
    varr->size = 0;
    varr->allocated_size = 1;
    varr->var_arr = malloc(sizeof(char *));
    varr->var_arr[0] = NULL;
    return (varr);
}

int main() {
    t_var_arr *varr = var_arr_create();

}