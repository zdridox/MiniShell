/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:31:03 by mamelnyk          #+#    #+#             */
/*   Updated: 2025/10/17 20:24:08 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*tail;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
			return (ft_lstclear(&new_lst, del), NULL);
		if (!new_lst)
		{
			new_lst = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		lst = lst->next;
	}
	return (new_lst);
}
/*
void	*test_fun(void *content)
{
	char	*src;
	char	*dst;
	size_t	i;

	src = (char *)content;
	dst = (char *)malloc(sizeof(char) * ft_strlen((char *)content) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_toupper((char)src[i]);
		i++;
	}
	dst[i] = '\0';
	return	((void *)dst);
}

void	this_time_realy_free_str(void *str)
{
	free(str);
}

void	realy_free_str(void *str)
{
	this_time_realy_free_str(str);
}

void	free_str(void *str)
{
	realy_free_str(str);
}

#include <stdio.h>

int	main(void)
{
	t_list	*first = NULL;
	t_list	*node1 = ft_lstnew("Hi");
	t_list	*node2 = ft_lstnew("Happy end of evaluation!");
	t_list	*node3 = ft_lstnew("And have a nice day!!!");

	ft_lstadd_back(&first, node1);
	ft_lstadd_back(&first, node2);
	ft_lstadd_back(&first, node3);

	t_list	*new_lst = ft_lstmap(first, test_fun, free_str);
	while (new_lst)
	{
		printf("%s\n", (char *)new_lst->content);
		new_lst = new_lst->next;
	}
	return (0);
}
*/
