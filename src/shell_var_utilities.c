#include "../headers/minishell.h"

void	add_shell_var(t_var_arr *varr, char *full_var)
{
	var_arr_add(varr, full_var);
}

void	remove_shell_var(t_var_arr *varr, char *var_name)
{
	size_t	i;

	i = -1;
	while (++i < varr->allocated_size)
	{
		if (!ft_strcmp(get_name_from_full_var(varr->var_arr[i]), var_name))
		{
			var_arr_remove_index(varr, i);
			break ;
		}
	}
}

void	set_shell_var_value(t_var_arr *varr, char *var_name, char *value)
{
	size_t	i;
	char	*str;

	i = -1;
	while (++i < varr->allocated_size)
	{
		if (!ft_strcmp(get_name_from_full_var(varr->var_arr[i]), var_name))
		{
			str = ft_strjoin_three(var_name, "=", value);
			free(varr->var_arr[i]);
			varr->var_arr[i] = ft_strdup(str);
			free(str);
			break ;
		}
	}
}

char	*get_shell_var_value(t_var_arr *varr, char *var_name)
{
	int	i;

	i = 0;
	while (i < varr->allocated_size)
	{
		if (!ft_strcmp(get_name_from_full_var(varr->var_arr[i]), var_name))
			return (get_value_from_full_var(varr->var_arr[i]));
		++i;
	}
	return (NULL);
}

char	*get_name_from_full_var(char *var)
{
	char	*name;
	int		i;

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
	char	*value;
	int		i;
	int		eqs_index;

	i = 0;
	while (var[i] != 0)
	{
		if (var[i] == '=')
			eqs_index = i;
		++i;
	}
	value = malloc((i - eqs_index));
	ft_memcpy(value, var + eqs_index, ((i - eqs_index) - 1));
	value[(i - eqs_index) - 1] = 0;
	return (value);
}
