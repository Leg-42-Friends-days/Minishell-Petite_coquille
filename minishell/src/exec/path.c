/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:14:15 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/16 17:20:59 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*find_path(t_env *env)
{
	char	*path;
    t_env   *current;

    if (!env)
        return (NULL);
    current = env;
	path = "PATH";
	while (current->key != NULL)
	{
		if (!ft_strncmp(current->key, path, 4))
			return (current->content);
		if (current->next)
            current = current->next;
	}
	return (NULL);
}

char	*browse(char **path, char *cmdd)
{
	char	*final_path;
	int		i;

	final_path = NULL;
	i = 0;
	while (path[i] != NULL)
	{
		if (final_path)
			free(final_path);
		final_path = ft_strjoin(path[i], cmdd);
		if (!final_path)
		{
			free(cmdd);
			return (NULL);
		}
		if (access(final_path, X_OK) == 0)
		{
			free(cmdd);
			return (final_path);
		}
		i++;
	}
	free(cmdd);
	free(final_path);
	return (NULL);
}

char	*right_path(char **path, char *cmd)
{
	char	*cmdd;
	char	*final_path;

	if (!path || !cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	cmdd = ft_strjoin("/", cmd);
	if (!cmdd)
		return (NULL);
	final_path = browse(path, cmdd);
	if (!final_path)
		return (NULL);
	free_cmd(path);
	return (final_path);
}

char    *find_cmd(t_env *env, char *cmd)
{
    char    *path;
    char    **tab_path;

    path = find_path(env);
    tab_path = ft_split(path, ':');
    if (!tab_path)
        return (NULL);
    return (right_path(tab_path, cmd));
}
