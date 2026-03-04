/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:26:44 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/04 15:48:40 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env *env, char *key)
{
	t_env	*current;

	if (!env)
		return (NULL);
	current = env;
	while (current->key != NULL)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key + 1)))
			return (current->content);
		if (current->next)
			current = current->next;
	}
	return (NULL);
}

t_env	*ft_getenv_node(t_env *env, char *key)
{
	t_env	*current;

	if (!env)
		return (NULL);
	current = env;
	while (current->key != NULL)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key + 1)))
			return (current);
		if (current->next)
			current = current->next;
	}
	return (NULL);
}

char	*define_target(char **cmd, t_env *env)
{
	char	*target;

	target = NULL;
	if (!cmd[1])
		target = ft_getenv(env, "HOME");
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "-", 2))
			target = ft_getenv(env, "OLDPWD");
		else if (cmd[2] != NULL)
		{
			write(2, "cd : too many arguments\n", 24);
			return (NULL);
		}
		else
			target = ft_strdup(cmd[1]);
	}
	return (target);
}

void	save_pwd(char *oldpwd, char *newpwd, t_env *env)
{
	t_env	*old_pwd_env;
	t_env	*pwd_env;

	(void)oldpwd;
	(void)newpwd;
	old_pwd_env = ft_getenv_node(env, "OLDPWD");
	pwd_env = ft_getenv_node(env, "PWD");
	free(old_pwd_env->content);
	old_pwd_env->content = ft_strdup(oldpwd);
	free(pwd_env->content);
	pwd_env->content = ft_strdup(newpwd);
}

int	ft_cd(char **cmd, t_env *env)
{
	char	*oldpwd;
	char	*target;

	target = NULL;
	target = define_target(cmd, env);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	save_pwd(oldpwd, getcwd(NULL, 0), env);
	//printf("old : %s\n", ft_getenv(env, "OLDPWD"));
	//printf("new : %s\n", ft_getenv(env, "PWD"));
	return (0);
}
