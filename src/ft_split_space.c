#include "parsing_fun.h"

static int	is_space(char a)
{
	return (a == 9 || a == 10 || a == 11 || a == 12 || a == 13 || a == 32);
}

static int	word_counter(char const *s)
{
	const char	*p;
	int			word_count;
	int			in_word;

	p = s;
	in_word = 0;
	word_count = 0;
	while (*p != '\0')
	{
		if (!is_space(*p))
			in_word = 1;
		if (is_space(*p) && in_word == 1)
		{
			word_count++;
			in_word = 0;
		}
		p++;
	}
	if (in_word == 1)
		word_count++;
	return (word_count);
}

static void	free_array(char **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**array_allocate(char const *s)
{
	char	**array;
	int		index;
	int		i;

	i = -1;
	index = 0;
	array = malloc((word_counter(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s != '\0')
	{
		if (!is_space(*s))
			i++;
		if ((is_space(*s) && i != -1) || (*(s + 1) == '\0' && i != -1))
		{
			array[index] = malloc(i + 2);
			if (!array[index++])
				return (free_array(array, index - 1), NULL);
			i = -1;
		}
		s++;
	}
	return (array);
}

char	**ft_split_space(char const *s)
{
	char	**array;
	int		index;
	int		i;

	i = -1;
	index = 0;
	if (!s)
		return (NULL);
	array = array_allocate(s);
	if (array == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (!is_space(*s))
		{
			array[index][i++ + 1] = *s;
		}
		if ((is_space(*s) && i != -1) || (*(s + 1) == '\0' && i != -1))
		{
			array[index++][i + 1] = '\0';
			i = -1;
		}
		s++;
	}
	return (array[index] = NULL, array);
}
