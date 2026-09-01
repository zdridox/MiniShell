/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:43:10 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/17 20:45:55 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_pointer;

	last_pointer = NULL;
	while (lst)
	{
		last_pointer = lst;
		lst = lst->next;
	}
	return (last_pointer);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*first = NULL;
	t_list	*node1 = ft_lstnew("Have a nice day!");
	t_list	*node2 = ft_lstnew("Hello!");

	ft_lstadd_front(&first, node1);
	ft_lstadd_front(&first, node2);

	printf("first->content = %s\n", (char *)first->content);
	printf("first->next->content = %s\n\n", (char *)first->next->content);
	printf("content of last element = %s\n", (char *)ft_lstlast(first)->content);

	free(node1);
	free(node2);
	return (0);
}
*/
