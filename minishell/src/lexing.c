/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:09:27 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/02 15:48:26 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_addnode(char *line)
{
	t_mini	*add_node;
	int		i;

	i = 0;
	add_node = malloc(sizeof(t_mini));
	if (!add_node)
		return (NULL);
	add_node->var = malloc(sizeof(char *) * 4);
	while (line[i])
	{
		if (line[i] != ' ')
		{
			add_node->var[i] = line[i];
		}
		i++;
	}
	add_node->var[2] = '\0';
	while (line[i])
	{
		if (line[i] == ' ')
		i ++;
	}
	line = line + i;
	return (add_node);
}

void	ft_add_back(t_mini **stack_a, t_mini *new)
{
	t_mini	*last;

	if (!stack_a || !new)
		return ;
	if (!*stack_a)
	{
		*stack_a = new;
		return ;
	}
	last = (*stack_a)->prev;
	last->next = new;
	new->prev = last;
	new->next = *stack_a;
	(*stack_a)->prev = new;
}

void	lexing(t_mini **mini_vars, char *line)
{
	t_mini *new;

	new = ft_addnode(line);
	ft_add_back(mini_vars, new);
}