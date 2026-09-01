/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:41:58 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/17 20:43:51 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst -> next;
	}
}
/*
#include <stdio.h>

void  print_fun(void *str)
{
  printf("%s\n", (char *)str);
}

int main(void)
{
  t_list  *first = NULL;
  t_list  *node1 = ft_lstnew("Hi");
  t_list  *node2 = ft_lstnew("I'm");
  t_list  *node3 = ft_lstnew("Here");

  ft_lstadd_back(&first, node1);
  ft_lstadd_back(&first, node2);
  ft_lstadd_back(&first, node3);
  ft_lstiter(first, print_fun);
}
*/
