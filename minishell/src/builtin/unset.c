/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:46:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/20 17:11:17 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	compare_unset(char *env, char *unset)
{
	int	i;

	i = 0;
	while (env[i] && unset[i] && env[i] == unset[i])
	{
		i++;
	}
	if (unset[i] == '\0' && (env[i] == '\0' || env[i] == '='))
		return (true);
	return (false);
}

void	call_unset(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (compare_unset(tmp->key, str) == true)
		{
			if (tmp->previous)
				tmp->previous->next = tmp->next;
			else
				env = tmp->next;
			if (tmp->next)
				tmp->next->previous = tmp->previous;
			free(tmp->key);
			if (tmp->free_export == true)
				free(tmp->content);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int	function_unset(t_env *env, char **unset)
{
	int	i;

	i = 1;
	while (unset[i])
	{
		call_unset(env, unset[i]);
		i++;
	}
	return (0);
}
