/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:35:46 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/18 11:30:36 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_minidelone(t_sub_token *lst)
{
	if (!lst)
		return ;
	if (lst->var)
		free(lst->var);
	free(lst);
}

void	ft_miniclear(t_token **lst)
{
	t_token		*cursor;
	t_sub_token	*sub_cursor;
	t_sub_token	*sub_next;
	t_token		*next;

	if (!lst || !*lst)
		return ;
	cursor = *lst;
	while (cursor)
	{
		sub_cursor = cursor->sub_token;
		while (sub_cursor)
		{
			sub_next = sub_cursor->next;
			ft_minidelone(sub_cursor);
			sub_cursor = sub_next;
		}
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	*lst = NULL;
}

void	printmini(t_token **mini)
{
	t_token		*cursor;
	t_sub_token	*sub_cursor;
	t_sub_token	*sub_next;
	t_token		*next;
	int			i;

	if (!mini || !*mini)
		return ;
	cursor = *mini;
	i = 0;
	while (cursor)
	{
		printf("token %d [%d]\n", i, cursor->type);
		sub_cursor = cursor->sub_token;
		while (sub_cursor)
		{
			sub_next = sub_cursor->next;
			printf("	sub_token : [%s]\n", sub_cursor->var);
			printf("	quote : [%d]\n", sub_cursor->quote);
			sub_cursor = sub_next;
		}
		next = cursor->next;
		cursor = next;
		i++;
	}
}
