/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:19:17 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/03 15:01:42 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strcat_env(char *s1, char *s2, int size)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*envjoin(char *s1, char *s2)
{
	int		len;
	char	*string;

	len = ft_strlen(s1) + ft_strlen(s2);
	string = strcat_env(s1, s2, len);
	free(s1);
	return (string);
}

t_env	*lstfirst_env(t_env *lst)
{
	t_env	*cursor;

	cursor = lst;
	while (cursor != NULL)
	{
		if (cursor->previous == NULL)
			return (cursor);
		cursor = cursor->previous;
	}
	return (cursor);
}

t_env	*lstadd_back_env(t_env *lst, char *key, char *value)
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

int	find_letter(char *envp, char letter)
{
	int	i;

	i = 0;
	if (!envp || !letter)
		return (0);
	while (envp[i] && envp[i] != letter)
		i++;
	return (i);
}

char	*get_key(char *envp)
{
	int		i;
	int		j;
	char	*str;

	i = find_letter(envp, '=');
	j = 0;
	str = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		str[j] = envp[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

t_env	*env_content(t_env *env, char **envp)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = getenv(key);
		env = lstadd_back_env(env, key, value);
		i++;
	}
	env = lstfirst_env(env);
	return (env);
}
