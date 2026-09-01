/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:55:27 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/30 14:18:36 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdlib.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
void	recursive_putnbr(size_t num, size_t *ret);
int		put_unsigned_int(unsigned int num);
int		ft_putnbr(int num);
void	recursive_puthex(size_t num, size_t *ret, const char *base_str);
int		ft_puthex(size_t num, const char *base_str);
void	recursive_put_adress(unsigned long num_adress, size_t *ret,
			const char *base_str);
int		ft_put_address(unsigned long num_adress, const char *base_str);

#endif
