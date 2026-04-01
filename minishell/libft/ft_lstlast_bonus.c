/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:31:36 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/14 17:31:38 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
			return (ptr);
		else
			ptr = ptr->next;
	}
	return (NULL);
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
	printf("dernier ptr : %p\n", current);
	printf("fonction %p", ft_lstlast(head));
}
 */