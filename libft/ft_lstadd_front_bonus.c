/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:40:45 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/14 07:24:58 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **first_node, t_list *new_node)
{
	new_node->next = *first_node;
	*first_node = new_node;
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
	printf("first->next->content = %s\n", (char *)first->next->content);

	free(node1);
	free(node2);
	return (0);
}
*/
