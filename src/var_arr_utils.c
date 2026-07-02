#include "../headers/minishell.h"

t_var_arr	*var_arr_create(void)
{
	t_var_arr	*varr;
	int			i;

	varr = malloc(sizeof(t_var_arr));
	varr->size = 0;
	varr->allocated_size = 5;
	varr->var_arr = malloc(sizeof(char *) * 5);
	i = -1;
	while (++i < 5)
	{
		varr->var_arr[i] = NULL;
	}
	return (varr);
}

void	var_arr_resize(t_var_arr *varr)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (varr->allocated_size + 5));
	i = -1;
	while (++i < varr->allocated_size)
	{
		if (varr->var_arr[i] != NULL)
		{
			new_arr[i] = ft_strdup(varr->var_arr[i]);
			free(varr->var_arr[i]);
		}
		else
		{
			new_arr[i] = NULL;
		}
	}
	i = -1;
	while (++i < 5)
		new_arr[varr->allocated_size + i] = NULL;
	varr->allocated_size += 5;
	free(varr->var_arr);
	varr->var_arr = new_arr;
}

void	var_arr_add(t_var_arr *varr, char *str)
{
	size_t	i;

	if (!varr || !str)
		return ;
	if (varr->allocated_size == varr->size)
		var_arr_resize(varr);
	i = 0;
	varr->var_arr[varr->size] = ft_strdup(str);
	varr->size += 1;
}

void	var_arr_remove_index(t_var_arr *varr, size_t index)
{
	if (!varr)
		return ;
	free(varr->var_arr[index]);
	varr->var_arr[index] = ft_strdup(varr->var_arr[varr->size - 1]);
	free(varr->var_arr[varr->size - 1]);
	varr->var_arr[varr->size - 1] = NULL;
	varr->size -= 1;
}

void	var_arr_free(t_var_arr *varr)
{
	int	i;

	if(!varr)
		return;
	i = -1;
	while (++i < varr->allocated_size)
	{
		if (varr->var_arr[i])
			free(varr->var_arr[i]);
	}
	free(varr->var_arr);
	free(varr);
}
