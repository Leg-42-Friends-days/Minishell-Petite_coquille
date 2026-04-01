/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:34:12 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/14 18:34:14 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr->next = new;
}
/* 
#include <stdio.h>

int main(void)
{
	t_list  *lst;
	t_list  *new;

	lst = malloc(sizeof(t_list));
	new = malloc(sizeof(t_list));
	printf("dernier %p\n", ft_lstlast(lst));
	printf("adresse struct new = %p\n", new);
	ft_lstadd_back(&lst, new);
	printf("dernier apres %p", ft_lstlast(lst));
} */