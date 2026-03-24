/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:03:07 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/24 15:40:54 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_table(char **table)
{
	int i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	if (table[i])
		free(table[i]);
	free(table);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env->next != NULL)
	{
		tmp = env->next;
		free(env->key);
		if (env->free_export == true)
			free(env->content);
		free(env);
		env = tmp;
	}
	if (env->free_export == true)
		free(env->content);
	free(env->key);
	free_table(env->table);
	free(env);
}

void	free_pwd(t_pwd *pwd)
{
	if (pwd->pwd)
		free(pwd->pwd);
	free(pwd);
}

