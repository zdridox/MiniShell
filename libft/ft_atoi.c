/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:16:58 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/10 19:24:21 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= '\a' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (sign * num);
}
/*
#include <stdio.h>

int main()
{
    char strToConvert[] = "-2147483649";
    int ConvByOrig = atoi(strToConvert);
    int ConvByFake = ft_atoi(strToConvert);

    printf("String to be Converted: %s\n", strToConvert);
    printf("Converted by    atoi: %d\n", ConvByOrig);
    printf("Converted by ft_atoi: %d\n", ConvByFake);

    return 0;
}
*/
