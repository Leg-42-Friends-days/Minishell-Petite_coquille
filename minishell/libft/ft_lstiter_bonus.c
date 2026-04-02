/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:30:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/16 18:30:35 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (!lst || !f)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		(*f)(ptr->content);
		ptr = ptr->next;
	}
}
/*
void	f(void *node)
{
	*(int *)node = *(int *)node + 1;
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
	ft_lstiter(head, f);
	printf("%d\n", *(int *)(head->content));
	printf("%d", *(int *)(current->content));
}
*/
