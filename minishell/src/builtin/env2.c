/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:35:21 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/02 17:00:30 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *envp)
{
	int		i;
	int		j;
	char	*str;

	if (!envp)
		return (NULL);
	i = find_letter(envp, '=');
	if (i == 0)
		return (NULL);
	j = 0;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
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
	char	*test;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		if (!key)
			return (env);
		test = getenv(key);
		if (!test)
			return (env);
		value = ft_strdup(test);
		if (!value)
			return (env);
		env = lstadd_back_env(env, key, value);
		if (!env)
			return (env);
		i++;
	}
	env = lstfirst_env(env);
	return (env);
}

int	affichage_env(t_env *env)
{
	while (env->next != NULL)
	{
		ft_printf(1, "%s", env->key);
		ft_printf(1, "=");
		ft_printf(1, "%s\n", env->content);
		env = env->next;
	}
	ft_printf(1, "%s", env->key);
	ft_printf(1, "=");
	ft_printf(1, "%s\n", env->content);
	return (0);
}

t_env	*mini_env(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("");
	env = lstadd_back_env(env, ft_strdup("PWD"), pwd);
	env = lstfirst_env(env);
	env = lstadd_back_env(env, ft_strdup("SHLVL"), ft_strdup("1"));
	env = lstadd_back_env(env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	// env = lstfirst_env(env);
	// env = lstadd_back_env(env, ft_strdup("OLDPWD"), ft_strdup(""));
	return (lstfirst_env(env));
}
