/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:26:44 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/09 11:56:22 by ibrouin-         ###   ########.fr       */
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
		if (!ft_strncmp(current->key, key, (ft_strlen(key) + 1)))
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
		if (!ft_strncmp(current->key, key, (ft_strlen(key) + 1)))
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
	{
		target = ft_getenv(env, "HOME");
		if (!target)
		{
			write(2, "cd: HOME nos set\n", 17);
			return (NULL);
		}
	}
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
			target = cmd[1];
	}
	return (target);
}

void	save_pwd(char *oldpwd, char *newpwd, t_env *env)
{
	t_env	*old_pwd_env;
	t_env	*pwd_env;

	old_pwd_env = ft_getenv_node(env, "OLDPWD");
	pwd_env = ft_getenv_node(env, "PWD");
	if (!old_pwd_env || !pwd_env)
		return ;
	if (newpwd == NULL)
	{
		if (pwd_env->content)
		{
			free(pwd_env->content);
			pwd_env->content = NULL;
		}
		return ;
	}
	else
	{
		free(pwd_env->content);
		pwd_env->content = NULL;
		pwd_env->content = ft_strdup(newpwd);
		free(newpwd);
	}
	if (oldpwd == NULL)
	{
		if (old_pwd_env->content)
		{
			free(old_pwd_env->content);
			old_pwd_env->content = NULL;
		}
		return ;
	}
	free(old_pwd_env->content);
	old_pwd_env->content = NULL;
	old_pwd_env->content = ft_strdup(oldpwd);
	free(oldpwd);
}

int	ft_cd(char **cmd, t_env *env)
{
	char	*oldpwd;
	char	*target;

	oldpwd = getcwd(NULL, 0);
	target = define_target(cmd, env);
	if (!target || target[0] == '\0')
		return (0);
	if (!oldpwd)
	{
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
		write(2, "No such file or directory", 25);
		write(2, "\n", 1);
		return (1);
	}
	if (chdir(target) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), strlen(strerror(errno)));
		write(2, "\n", 1);
		return (1);
	}
	if (cmd[1] && !ft_strncmp(cmd[1], "-", 2))
	{
		write(1, target, ft_strlen(target));
		write(1, "\n", 1);
	}
	save_pwd(oldpwd, getcwd(NULL, 0), env);
	//printf("old : %s\n", ft_getenv(env, "OLDPWD"));
	//printf("new : %s\n", ft_getenv(env, "PWD"));
	return (0);
}
