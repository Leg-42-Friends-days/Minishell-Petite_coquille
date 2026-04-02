/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:00:28 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/16 19:00:31 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rslt;
	t_list	*newnode;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	rslt = NULL;
	while (lst != NULL)
	{
		content = (*f)(lst->content);
		if (!content)
			return (ft_lstclear(&rslt, del), NULL);
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			ft_lstclear(&rslt, del);
			del(content);
			return (NULL);
		}
		ft_lstadd_back(&rslt, newnode);
		lst = lst->next;
	}
	return (rslt);
}
/* 
void	*f(void *node)
{
	*(int *)node = *(int *)node + 1;
	return (node);
}

void	del(void *node)
{
	free(node);
}

#include <stdio.h>

int	main(void)
{
	t_list	*head;
	t_list	*current;
	int		content1;
	int		content2;

	head = malloc(sizeof(t_list));
	current = malloc(sizeof(t_list));

	head->next = current;
	content1 = 45;
	head->content = &content1;
	printf("%d\n", *(int *)(head->content));
	content2 = 22;
	current->content = &content2;
	printf("%d\n", *(int *)(current->content));
	head = ft_lstmap(head, f, del);
	printf("%d\n", *(int *)(head->content));
	printf("%d", *(int *)(current->content));
} */