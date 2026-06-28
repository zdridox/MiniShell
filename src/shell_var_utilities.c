#include "../headers/minishell.h"

void	remove_shell_var(t_var_arr *varr, char *var_name)
{
	size_t	i;

	if (!var_name || !varr)
		return ;
	i = -1;
	while (++i < varr->allocated_size)
	{
		if (!var_name_cmp(var_name, varr->var_arr[i]))
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

	if (!var_name || !value || !varr)
		return ;
	i = -1;
	str = NULL;
	while (++i < varr->allocated_size)
	{
		if (!var_name_cmp(var_name, varr->var_arr[i]))
		{
			str = ft_strjoin_three(var_name, "=", value);
			free(varr->var_arr[i]);
			varr->var_arr[i] = ft_strdup(str);
			break ;
		}
	}
	if (str == NULL)
	{
		str = ft_strjoin_three(var_name, "=", value);
		var_arr_add(varr, str);
	}
	free(str);
}

void	set_shell_var_from_full_var(t_var_arr *varr, char *full_var)
{
	size_t	i;

	if (!full_var || !varr)
		return ;
	i = -1;
	while (++i < varr->allocated_size)
	{
		if (!fvar_to_fvar_name_cmp(full_var, varr->var_arr[i]))
		{
			free(varr->var_arr[i]);
			varr->var_arr[i] = ft_strdup(full_var);
			return ;
		}
	}
	var_arr_add(varr, full_var);
}

char	*get_shell_var_value(t_var_arr *varr, char *var_name) // add quote handling
{
	int	i;

	i = 0;
	if (!var_name || !varr)
		return (NULL);
	while (i < varr->allocated_size)
	{
		if (!var_name_cmp(var_name, varr->var_arr[i]))
			return (get_value_from_full_var(varr->var_arr[i]));
		++i;
	}
	return (NULL);
}

char	*get_name_from_full_var(char *var)
{
	char	*name;
	int		i;

	if (!var)
		return (NULL);
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
	char	*p;

	if (!var)
		return (NULL);
	p = var;
	while (*p != '=')
		++p;
	++p;
	return (p);
}

// char	*get_value_from_full_var(char *var)
// {
// 	char	*value;
// 	int		i;
// 	int		eqs_index;

// 	if (!var)
// 		return (NULL);
// 	i = 0;
// 	while (var[i] != 0)
// 	{
// 		if (var[i] == '=')
// 			eqs_index = i;
// 		++i;
// 	}
// 	value = malloc((i - eqs_index));
// 	ft_memcpy(value, var + eqs_index + 1, ((i - eqs_index) - 1));
// 	value[(i - eqs_index) - 1] = 0;
// 	return (value);
// }
