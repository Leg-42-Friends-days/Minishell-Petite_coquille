/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:28:19 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/25 13:28:20 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_table_env(t_env *env)
{
	int	i;

	env = lstfirst_env(env);
	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*ft_envdup(t_env *env)
{
	char	*key;
	char	*content;

	if (!env || !env->key)
		return (NULL);
	key = ft_strjoin(env->key, "=");
	if (!key)
		return (NULL);
	if (!env->content)
		return (key);
	content = ft_strjoin(key, env->content);
	free(key);
	return (content);
}

char	**initiate_table_env(t_env *env)
{
	char	**table;
	int		i;

	env = lstfirst_env(env);
	i = 0;
	table = malloc(sizeof(char *) * (len_table_env(env) + 1));
	if (!table)
		return (NULL);
	while (env != NULL)
	{
		table[i] = ft_envdup(env);
		if (!table[i])
			return (NULL);
		i++;
		env = env->next;
	}
	table[i] = NULL;
	return (table);
}
