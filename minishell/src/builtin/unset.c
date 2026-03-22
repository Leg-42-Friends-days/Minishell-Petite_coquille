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
	t_env *tmp;
	
	tmp = env;
	while (tmp != NULL)
	{
		if (compare_unset(env->key, str) == true)
		{
			printf("true\n");
		}
		tmp = tmp->next;
	}
}

int	function_unset(t_env *env, char **unset)
{
	int i;

	i = 0;

	while (unset[i])
	{
		printf("UNSET\n")																						;
		call_unset(env, unset[i]);
		i++;
	}
	return (0);
}

// int	function_unset(t_env *env, char **unset)
// {
// 	t_env	*tmp;
// 	t_env	*head;

// 	head = lstfirst_env(env);
// 	env = head;
// 	while (env != NULL)
// 	{
// 		if (compare_unset(env->key, *unset) == true)
// 		{
// 			tmp = env->next;
// 			if (env->previous)
// 				env->previous->next = env->next;
// 			else
// 				head = env->next;
// 			if (env->next)
// 				env->next->previous = env->previous;
// 			free(env->key);
// 			if (env->free_export == true)
// 				free(env->content);
// 			free(env);
// 			env = tmp;
// 		}
// 		else
// 			env = env->next;
// 	}
// 	return (0);
// }
