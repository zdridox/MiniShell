/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:43:45 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/14 22:02:28 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
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
	ft_lstdelone(first->next, del);
	printf("node1->content = %s\n", (char *)node1->content);
	printf("node1->next = %p\n", node1->next);
	ft_lstdelone(first, del);
	return (0);
}
*/
