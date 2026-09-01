/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:57:47 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/17 17:20:41 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node_ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node_ptr = *lst;
	while (node_ptr->next)
	{
		node_ptr = node_ptr->next;
	}
	node_ptr->next = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*first = NULL;
	t_list	*node1 = ft_lstnew("Hi, I'm first");
	t_list	*node2 = ft_lstnew("Hi, I'm second");

	ft_lstadd_front(&first, node1);
	ft_lstadd_back(&first, node2);

	printf("first->content = %s\n", (char *)first->content);
	printf("first->next->content = %s\n", (char *)first->next->content);

	free(node1);
	free(node2);
	return (0);
}
*/
