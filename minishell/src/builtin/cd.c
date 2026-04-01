/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:26:44 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/01 14:23:34 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*define_target(char **cmd, t_env *env, int *error_code)
{
	char	*target;

	target = NULL;
	if (!cmd[1])
		return (target_home(env, error_code, target));
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "-", 2))
			return (ft_getenv(env, "OLDPWD"));
		if (invalid_option(cmd) == 2 && cmd[2])
			return (cmd[2]);
		if (invalid_option(cmd) == 2 && !cmd[2])
			return (target_home(env, error_code, target));
		if (invalid_option(cmd) == 1)
			return (print_invalid_option(error_code));
		else if (cmd[2])
		{
			write(2, "cd : too many arguments\n", 24);
			*error_code = 1;
			return (NULL);
		}
		else
			target = cmd[1];
	}
	return (target);
}

void	save_pwd(char *newpwd, t_env *env)
{
	t_env	*old_pwd_env;
	t_env	*pwd_env;

	if (!newpwd)
		return ;
	old_pwd_env = ft_getenv_node(env, "OLDPWD");
	pwd_env = ft_getenv_node(env, "PWD");
	if (!old_pwd_env || !pwd_env)
	{
		free(newpwd);
		return ;
	}
	free(old_pwd_env->content);
	old_pwd_env->content = NULL;
	old_pwd_env->content = ft_strdup(pwd_env->content);
	free(pwd_env->content);
	pwd_env->content = NULL;
	pwd_env->content = ft_strdup(newpwd);
	free(newpwd);
}

int	print_no_such_file(char *target)
{
	write(2, "minishell: cd: ", 15);
	write(2, target, ft_strlen(target));
	write(2, ": ", 2);
	write(2, "No such file or directory", 25);
	write(2, "\n", 1);
	return (1);
}

int	print_error_target(char **cmd, char *oldpwd)
{
	write(2, "minishell: cd: ", 15);
	write(2, cmd[1], ft_strlen(cmd[1]));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
	free(oldpwd);
	return (1);
}

int	ft_cd(char **cmd, t_env *env)
{
	char	*oldpwd;
	char	*target;
	int		error_code;

	error_code = 0;
	oldpwd = getcwd(NULL, 0);
	target = define_target(cmd, env, &error_code);
	if (!target || target[0] == '\0')
	{
		free(oldpwd);
		return (error_code);
	}
	if (!oldpwd && error_code != 42)
		return (print_no_such_file(target));
	if (chdir(target) < 0)
		return (print_error_target(cmd, oldpwd));
	if (cmd[1] && !ft_strncmp(cmd[1], "-", 2))
	{
		write(1, target, ft_strlen(target));
		write(1, "\n", 1);
	}
	save_pwd(getcwd(NULL, 0), env);
	free(oldpwd);
	return (0);
}
