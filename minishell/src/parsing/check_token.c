/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:23:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/24 21:51:36 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	lst_last_token(t_token **token)
{
	t_token	*current;

	current = (*token);
	while (current->next != NULL)
		current = current->next;
	if (current->type > 6)
	{
		token = &current;
		return (true);
	}
	return (false);
}

bool	next_token(t_token **token)
{
	while ((*token)->next != NULL)
	{
		if ((*token)->type > 6 && (*token)->next->type > 6)
			return (true);
		else if ((((*token)->type == 6) || ((*token)->type == 5))
			&& ((*token)->next->type > 0 && (*token)->next->type < 5))
			return (false);
		else if (((*token)->type > 0 && (*token)->type < 5)
			&& (!(*token)->next || (*token)->next->type != WORD))
			return (true);
		else if ((*token)->type == 0 && (*token)->next->type == 5)
		{
			(*token) = (*token)->next;
			return (true);
		}
		else if (((*token)->type == 5 && (*token)->next->type == 6))
		{
			(*token) = (*token)->next;
			return (true);
		}
		else if (((*token)->type > 0 && (*token)->type < 5)
			&& ((*token)->next->type > 0 && (*token)->next->type < 5))
			return (true);
		(*token) = (*token)->next;
	}
	return (false);
}

bool	check_token(t_token **token)
{
	if ((*token)->type > 6 || next_token(token) == 1
		|| lst_last_token(token) == 1)
		return (true);
	return (false);
}
