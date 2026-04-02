/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:23:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/02 20:27:54 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_par(t_token *token)
{
	int	in_par;
	int	l_par;
	int	r_par;

	in_par = 0;
	l_par = 0;
	r_par = 0;
	while (token)
	{
		if (token->type == L_PAR)
		{
			in_par = 1;
			l_par ++;
		}
		if (token->type == R_PAR)
		{
			if (in_par == 0)
				return (1);
			r_par ++;
		}
		token = token->next;
	}
	if (l_par != r_par)
		return (1);
	return (0);
}

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
		else if ((*token)->next && ((((*token)->type == 0
						&& (*token)->next->type == 5)
					|| ((*token)->type == 5 && (*token)->next->type == 6))
				|| (((*token)->type > 0 && (*token)->type < 5)
					&& (*token)->next->type == PIPE)))
		{
			(*token) = (*token)->next;
			return (true);
		}
		else if (((*token)->type > 0 && (*token)->type < 5)
			&& (!(*token)->next || (*token)->next->type != WORD))
			return (true);
		(*token) = (*token)->next;
	}
	return (false);
}

bool	check_token(t_token **token)
{
	t_token	*current;

	current = *token;
	if ((*token)->type > 6 || next_token(token) == 1)
		return (true);
	if (handle_par(current) == 1)
		return (true);
	if (lst_last_token(token) == 1)
		return (true);
	return (false);
}
