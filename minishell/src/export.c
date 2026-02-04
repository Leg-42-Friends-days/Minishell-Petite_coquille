/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:20:36 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/04 10:54:55 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstadd_back_exp(t_env *lst, char *key, char *value)
{
	t_env	*last;
	t_env	*curseur;

	last = malloc(sizeof(t_env));
	if (!last)
		return (NULL);
	last->key = key;
	last->content = value;
	last->next = NULL;
	if (lst == NULL)
	{
		last->previous = NULL;
		return (last);
	}
	curseur = lst;
	while (curseur->next != NULL)
		curseur = curseur->next;
	curseur->next = last;
	last->previous = curseur;
	return (last);
}

// int	function_export(t_env *env, t_token *info)
// {
// 	char	*key;
// 	char	*content;

	
// 	return (0);
// }
