#include "minishell.h"

void	var_arr_fill(t_var_arr *varr, char **array, t_shell *shell)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
	{
		var_arr_add(varr, array[i], shell);
	}
}

void	var_arr_print(t_var_arr *varr)
{
	int	i;

	i = -1;
	while (++i < (int)varr->size)
		ft_printf("%s\n", varr->var_arr[i]);
}
