/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:28:23 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/26 12:17:22 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	function_export(t_env *env, char **cmd, int *error)
{
	char	*key;
	char	*content;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (get_equal(cmd[i], error) == 0)
		{
			i++;
			continue ;
		}
		key = get_key(cmd[i]);
		content = get_content(cmd[i]);
		if (key_exist(env, key, content) == true)
			i++;
		else
		{
			env = lstadd_back_exp(env, key, content);
			env = lstfirst_env(env);
			i++;
		}
	}
	return (*error);
}

bool	key_exist(t_env *env, char *key, char *content)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, -1) == 0)
		{
			free(env->content);
			env->content = ft_strdup(content);
			free(content);
			free(key);
			return (true);
		}
		env = env->next;
	}
	env = lstfirst_env(env);
	return (false);
}
