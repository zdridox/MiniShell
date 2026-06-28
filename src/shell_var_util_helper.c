#include "../headers/minishell.h"

int	var_name_cmp(char *var_name, char *full_var)
{
	size_t	size;
	size_t	i;

	if (!var_name || !full_var)
		return (-1);
	size = ft_strlen(var_name);
	i = 0;
	while (i < size && full_var[i] && full_var[i + 1])
	{
		if (var_name[i] != full_var[i])
			return (var_name[i] - full_var[i]);
		++i;
	}
	if (full_var[i] != '=')
		return (1);
	return (0);
}

int	fvar_to_fvar_name_cmp(char *full_var1, char *full_var2)
{
	size_t	i;

	if (!full_var1 || !full_var2)
		return (-1);
	i = 0;
	while (full_var1[i] && full_var2[i])
	{
		if (full_var1[i] != full_var2[i])
			return (full_var1[i] - full_var2[i]);
		if (full_var1[i] == '=' && full_var2[i] == '=')
			return (0);
		++i;
	}
	return (1);
}