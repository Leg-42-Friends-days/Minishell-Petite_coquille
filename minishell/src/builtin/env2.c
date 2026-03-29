/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:35:21 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/26 12:08:29 by mickzhan         ###   ########.fr       */
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
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = ft_strdup(getenv(key));
		env = lstadd_back_env(env, key, value);
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


t_env *mini_env(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("");
	env = lstadd_back_env(env, ft_strdup("PWD"), pwd);
	env = lstfirst_env(env);
	env = lstadd_back_env(env, ft_strdup("SHLVL"), ft_strdup("1"));
	// env = lstfirst_env(env);
	// env = lstadd_back_env(env, ft_strdup("OLDPWD"), ft_strdup(""));
	return (lstfirst_env(env));
}
