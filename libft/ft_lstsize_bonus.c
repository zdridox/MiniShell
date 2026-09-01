/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 07:27:10 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/14 15:42:45 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
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
	printf("size = %d\n", ft_lstsize(first));

	free(node1);
	free(node2);
	return (0);
}
*/
