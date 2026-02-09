/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:08:35 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/09 16:33:43 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*addnode(t_token_type type)
{
	t_token	*add_node;

	add_node = malloc(sizeof(t_token));
	if (!add_node)
		return (NULL);
	add_node->token_state = 1;
	add_node->sub_token = NULL;
	add_node->type = type;
	add_node->next = NULL;
	add_node->prev = NULL;
	return (add_node);
}

t_sub_token	*add_subnode(char *buffer, t_quote quote)
{
	t_sub_token	*add_sub_node;

	add_sub_node = malloc(sizeof(t_sub_token));
	if (!add_sub_node)
		return (NULL);
	add_sub_node->var = ft_strdup(buffer);
	add_sub_node->quote = quote;
	add_sub_node->next = NULL;
	add_sub_node->prev = NULL;
	return (add_sub_node);
}

t_token	*find_last(t_token **lst)
{
	t_token	*last;

	if (!lst)
		return (NULL);
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	lstadd_back(t_token *new, t_token **lst)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	lstadd_sub_back(t_sub_token *new, t_token **lst)
{
	t_sub_token	*last;
	t_token		*current;

	if (!lst || !new)
		return ;
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	if (!current->sub_token)
	{
		current->sub_token = new;
		return ;
	}
	last = current->sub_token;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}
