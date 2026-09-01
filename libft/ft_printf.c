/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:12:37 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/11/17 20:38:30 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include <stdarg.h>

static int	put_arg(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'u')
		return (put_unsigned_int(va_arg(ap, unsigned int)));
	else if (c == 'p')
		return (ft_put_address((unsigned long)va_arg(ap, void *),
				"0123456789abcdef"));
	else if (c == 'x')
		return (ft_puthex(va_arg(ap, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_puthex(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	else if (c == '%')
		return (ft_putchar('%'));
	else
		return (0);
}

static void	ft_vprintf(const char *fmt, va_list ap, size_t *ret)
{
	size_t	i;
	size_t	printing_len;

	i = 0;
	while (fmt[i])
	{
		printing_len = 0;
		while (fmt[i] && fmt[i] != '%')
		{
			printing_len++;
			i++;
		}
		if (printing_len)
			*ret += write(1, &fmt[i - printing_len], printing_len);
		if (fmt[i] == '%')
		{
			*ret += put_arg(fmt[++i], ap);
			i++;
		}
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	size_t	ret;

	ret = 0;
	va_start(ap, fmt);
	ft_vprintf(fmt, ap, &ret);
	va_end(ap);
	return (ret);
}
/*
#include <stdio.h>

int	main(void)
{
	int	num;

	num = 15;
	//printf("My = %d\n", ft_printf("%p\n", (void *)num)); 
	//printf("Or = %d\n", printf("%p\n", (void *)num)); 
	ft_printf("Hello World!");
	//ft_printf("%d", num);
	return (0);
}
*/
