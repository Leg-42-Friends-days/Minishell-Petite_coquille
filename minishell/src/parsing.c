/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:05:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/10 18:57:19 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*lstlast(t_token *lst)
// {
// 	t_token	*cursor;

// 	cursor = lst;
// 	while (cursor != NULL)
// 	{
// 		if (cursor->next == NULL)
// 			return (cursor);
// 		cursor = cursor->next;
// 	}
// 	return (cursor);
// }

int	liste_compteur(t_token *token)
{
	int	i;

	i = 0;
	while (token->next != NULL)
	{
		i++;
		token = token->next;
	}
	if (token)
		i++;
	return (i);
}

void	rendu_args(t_token *token, char **cmd)
{
	int	i;

	i = 0;
	while (token->next != NULL)
	{
		cmd[i] = token->sub_token->var;
		i++;
		token = token->next;
	}
}

// geten -> "token"
int	parser(t_token *token)
{
    printf("%s", getenv(token->sub_token->var));
	return (0);
}