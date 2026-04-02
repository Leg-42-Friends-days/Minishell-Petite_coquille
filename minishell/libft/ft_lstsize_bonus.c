/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:35:03 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/14 16:35:07 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cmpt;
	t_list	*ptr;

	if (!lst)
		return (0);
	cmpt = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		cmpt++;
		ptr = ptr->next;
	}
	return (cmpt);
}
/* 
#include <stdio.h>

int	main(void)
{
	t_list	*head;
	t_list	*current;

	head = malloc(sizeof(t_list));
	current = malloc(sizeof(t_list));
	head->next = current;
	current =  malloc(sizeof(t_list));
	head->next->next = current;
	printf("%d", ft_lstsize(head));
}
 */
