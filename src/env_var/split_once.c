#include "minishell.h"

int	*split_once_counter(char *str, char delimeter)
{
	int	*sizes;
	int	i;
	int	d_flag;

	sizes = malloc(2 * sizeof(int));
	sizes[0] = 0;
	sizes[1] = 0;
	d_flag = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == delimeter && d_flag == 0)
		{
			d_flag = 1;
			continue ;
		}
		if (d_flag == 0)
			++sizes[0];
		else
			++sizes[1];
	}
	return (sizes);
}

char	**split_once(char *str, char delimeter)
{
	char	**splitted;
	int		*sizes;

	sizes = split_once_counter(str, delimeter);
	splitted = malloc(3 * sizeof(char *));
	splitted[0] = malloc(sizes[0] + 1);
	splitted[1] = malloc(sizes[1] + 1);
	ft_strlcpy(splitted[0], str, sizes[0] + 1);
	splitted[0][sizes[0]] = 0;
	if (sizes[1] == 0)
	{
		free(splitted[1]);
		splitted[1] = NULL;
	}
	else
	{
		ft_strlcpy(splitted[1], str + sizes[0] + 1, sizes[1] + 1);
		splitted[1][sizes[1]] = 0;
	}
	splitted[2] = NULL;
	free(sizes);
	return (splitted);
}
