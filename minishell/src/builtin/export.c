/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:20:36 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/20 16:16:07 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lstadd_back_exp(t_env *lst, char *key, char *value)
{
	t_env	*last;
	t_env	*curseur;

	if (key == NULL || value == NULL)
		return (NULL);
	last = malloc(sizeof(t_env));
	if (!last)
		return (NULL);
	last->key = key;
	last->content = value;
	last->free_export = true;
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

char	*get_content(char *test)
{
	int		i;
	int		j;
	char	*str;

	i = find_letter(test, '=');
	j = 0;
	while (test[i])
	{
		j++;
		i++;
	}
	str = malloc(sizeof(char) * (j + 1));
	i = find_letter(test, '=') + 1;
	j = 0;
	while (test[i])
	{
		str[j] = test[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

bool	get_equal(char *test)
{
	int	i;

	i = 0;
	while (test[i])
	{
		if (test[i] == '=')
			return (true);
		i++;
	}
	return (false);
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

int	function_export(t_env *env, char **cmd)
{
	char	*key;
	char	*content;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (get_equal(cmd[i]) == 0)
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
	return (0);
}
