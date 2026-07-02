#include "../headers/minishell.h"

t_vars	*vars_init(void)
{
	t_vars	*vars;
	int		i;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->vars = malloc(sizeof(t_variable) * 5);
	if (!vars->vars)
		return (NULL);
	vars->size = 0;
	vars->allocated_size = 5;
	vars->first_free_index = 0;
	i = -1;
	while (++i < 5)
	{
		vars->vars[i].name = NULL;
		vars->vars[i].value = NULL;
	}
	return (vars);
}

void	vars_resize(t_vars *vars)
{
}

void	vars_add(t_vars *vars, t_variable var)
{
}

void	vars_removeIndex(t_vars *vars, size_t index)
{
}

void	vars_free(t_vars *vars)
{
}

// work on a normal char** and when removing from inside just move last into the new free slot