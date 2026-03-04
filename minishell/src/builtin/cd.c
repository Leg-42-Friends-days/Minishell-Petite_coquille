/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:26:44 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/04 11:33:39 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env *env, char *key)
{
    t_env   *current;

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

char	*define_target(char **cmd, t_env *env)
{
	char	*target;

	target = NULL;
	if (!cmd[1])
	{
		target = ft_getenv(env, "HOME");
	}
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "-", 2))
		{
			target = ft_getenv(env, "OLDPWD");
		}
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

int	ft_cd(char **cmd, t_env *env)
{
	char	*target;

	target = NULL;
	target = define_target(cmd, env);
	printf("%s\n", target);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

// void	cd_move_directory(t_pwd *pwd, t_parse *dir)
// {
// 	if (chdir(parse->) != -1)
// 	{
// 		printf("success");
// 	}
// 	perror("chdir");
// }
