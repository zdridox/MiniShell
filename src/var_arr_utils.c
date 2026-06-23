#include "../headers/minishell.h"

t_var_arr	*var_arr_create(void)
{
	t_var_arr	*varr;

	varr = malloc(sizeof(t_var_arr));
	varr->size = 0;
	varr->allocated_size = 1;
	varr->var_arr = malloc(sizeof(char *));
	varr->var_arr[0] = NULL;
	return (varr);
}

void	var_arr_add(t_var_arr **varr, char *str)
{
	int	i;

	if ((*varr)->allocated_size == (*varr)->size)
	{
		*varr = resize_str_arr(*varr, (*varr)->allocated_size + 5);
		(*varr)->allocated_size += 5;
		i = 0;
		while (i < 5)
			(*varr)->var_arr[((*varr)->size - 1) + i++] = NULL;
	}
	i = 0;
	while ((*varr)->var_arr[i] != NULL)
		++i;
	(*varr)->var_arr[i] = ft_strdup(str);
	(*varr)->size += 1;
}

void	var_arr_remove_index(t_var_arr **varr, size_t index)
{
	free((*varr)->var_arr[index]);
	(*varr)->var_arr[index] = NULL;
	(*varr)->size -= 1;
}

int	main(void)
{
	t_var_arr *varr = var_arr_create();
}