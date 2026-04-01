/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:20:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 14:24:15 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env *env, char *key)
{
	t_env	*current;

	if (!env)
		return (NULL);
	current = env;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key, (ft_strlen(key) + 1)))
			return (current->content);
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
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key, (ft_strlen(key) + 1)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	invalid_option(char **cmd)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (cmd[1][i] == '-')
	{
		i++;
	}
	if (cmd[1][i] == '\0')
		r = 1;
	if (i == 2)
		r = 2;
	return (r);
}

char	*target_home(t_env *env, int *error_code, char *target)
{
	target = ft_getenv(env, "HOME");
	if (!target)
	{
		write(2, "cd: HOME not set\n", 17);
		*error_code = 1;
		return (NULL);
	}
	*error_code = 42;
	return (target);
}

char	*print_invalid_option(int *error_code)
{
	write(2, "cd: --: invalid option\n", 23);
	*error_code = 2;
	return (NULL);
}
