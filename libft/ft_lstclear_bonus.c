/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:05:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/17 20:35:06 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next_node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_node;
	}
	*lst = NULL;
}
/*
#include <stdio.h>

void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*first = NULL;
	t_list	*node1 = ft_lstnew(ft_strdup("I`m alive!"));
	t_list	*node2 = ft_lstnew(ft_strdup("Hello!"));

	ft_lstadd_back(&first, node1);
	ft_lstadd_back(&first, node2);
	printf("first->content = %s\n", (char *)first->content);
	printf("first->next->content = %s\n", (char *)first->next->content);
	ft_lstclear(&first, del);
	return (0);
}
*/
