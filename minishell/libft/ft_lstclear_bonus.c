/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:55:29 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/16 17:55:34 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		next = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = next;
	}
	*lst = NULL;
}
