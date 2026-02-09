/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:35:46 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/09 16:34:37 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_minidelone(t_token *lst)
{
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

void	printmini(t_token **mini)
{
	int	i;

	i = 1;
	if (!*mini)
	{
		printf("error\n");
		return ;
	}
	while ((*mini)->next != NULL)
	{
		printf("token %d [%d]\n", i, (*mini)->type);
		while ((*mini)->sub_token->next != NULL)
		{
			printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
			printf("	quote : [%d]\n", (*mini)->sub_token->quote);
			(*mini)->sub_token = (*mini)->sub_token->next;
		}
		if ((*mini)->sub_token->var)
		{
			printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
			printf("	quote : [%d]\n", (*mini)->sub_token->quote);
			*mini = (*mini)->next;
		}
		i ++;
	}
	printf("token %d [%d]\n", i, (*mini)->type);
	while ((*mini)->sub_token->next != NULL)
	{
		printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("	quote : [%d]\n", (*mini)->sub_token->quote);
		(*mini)->sub_token = (*mini)->sub_token->next;
	}
	if ((*mini)->sub_token->var)
	{
		printf("	sub_token : [%s]\n", (*mini)->sub_token->var);
		printf("	quote : [%d]\n", (*mini)->sub_token->quote);
	}
}
