/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:23:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/17 11:36:31 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	lst_last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	if (token->type != 0)
		return (true);
	return (false);
}

bool	last_next_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->next != NULL)
	{
		if (token->type != 0 && token->next->type != 0)
			return (true);
		token = token->next;
	}
	return (false);
}

bool	check_token(t_token *token)
{
	if (token->type != 0 || lst_last_token(token) == 1
		|| last_next_token(token) == 1)
		return (true);
	return (false);
}