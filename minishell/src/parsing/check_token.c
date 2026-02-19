/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:23:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/02/18 14:26:32 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	lst_last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	if (token->type > 6)
		return (true);
	return (false);
}

bool	last_next_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->next != NULL)
	{
		if (token->type > 6 && token->next->type > 6)
			return (true);
		else if ((token->type > 0 && token->type < 7) && (token->next->type > 0 && token->next->type < 7))
			return (true);
		else if ((token->type == 5 || token->type == 6) && (token->next->type == 5 || token->next->type == 6))
			return (true);
		token = token->next;
	}
	return (false);
}

bool	check_token(t_token *token)
{
	if (token->type > 6 || lst_last_token(token) == 1
		|| last_next_token(token) == 1)
		return (true);
	return (false);
}