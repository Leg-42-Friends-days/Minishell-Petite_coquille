/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:03:07 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 19:41:32 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_table(char **table)
{
	int	i;

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
	free(env);
}

void	free_pwd(t_pwd *pwd)
{
	if (pwd->pwd)
		free(pwd->pwd);
	free(pwd);
}

void	free_before_exit(t_global *global)
{
	ft_miniclear(&(global->head));
	free_parser(global->ast);
	if (global->env)
		free_env(global->env);
	free(global->error_code);
	free(global->what_free);
	free(global->here_doc_error);
	free(global);
}