/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:20:36 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/18 15:14:38 by mickzhan         ###   ########.fr       */
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
		printf("key : %s\n", key);
		printf("content : %s\n", content);
		env = lstadd_back_exp(env, key, content);
		env = lstfirst_env(env);
		i++;
	}
	return (0);
}
