/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:46:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/09 15:18:44 by mickzhan         ###   ########.fr       */
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

t_env	*function_unset(t_env *env, char *unset)
{
	t_env	*tmp;
	t_env	*head;

	head = lstfirst_env(env);
	env = head;
	while (env != NULL)
	{
		if (compare_unset(env->key, unset) == true)
		{
			tmp = env->next;
			if (env->previous)
				env->previous->next = env->next;
			else
				head = env->next;
			if (env->next)
				env->next->previous = env->previous;
			free(env->key);
			if (env->free_export == true)
				free(env->content);
			free(env);
			env = tmp;
		}
		else
			env = env->next;
	}
	return (head);
}
