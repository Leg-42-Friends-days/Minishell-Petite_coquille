/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:46:10 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/14 15:46:13 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/* 
#include <stdio.h>

int main(void)
{
	t_list  *lst;
	t_list  *new;

	lst = malloc(sizeof(t_list));
	printf("adresse struct lst = %p\n", lst);
	new = malloc(sizeof(t_list));
	printf("adresse struct new = %p\n", new);
	ft_lstadd_front(&lst, new);
	printf("new->next = %p\n", new->next);
	printf("pointeur que lst pointe %p", lst);
} */