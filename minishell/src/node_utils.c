/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:35:46 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/03 11:44:47 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minidelone(t_token *lst)
{
	free(lst->var);
	//free(lst->type);
	free(lst);
}

void	ft_miniclear(t_token **lst)
{
	t_token	*cursor;
	t_token	*next;

	if (!lst || !*lst)
		return ;
	cursor = *lst;
	while (cursor)
	{
		next = cursor->next;
		ft_minidelone(cursor);
		cursor = next;
	}
	*lst = NULL;
}
