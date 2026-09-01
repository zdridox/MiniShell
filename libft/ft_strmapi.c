/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:17:32 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/20 20:34:16 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*fun)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*modified_str;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	modified_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!modified_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		modified_str[i] = fun(i, str[i]);
		i++;
	}
	modified_str[i] = '\0';
	return (modified_str);
}

/*
char	my_fun(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ('*');
	else
		return (c);
}

int	main(void)
{
	char	str[] = "Happy evaluation!!!";

	printf("str: \"%s\"\nmodified_str: \"%s\"\n", str, ft_strmapi(str, my_fun));
}
*/
