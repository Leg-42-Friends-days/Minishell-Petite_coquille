/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:14:15 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/23 09:43:46 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*find_path(t_env *env)
{
	char	*path;
	t_env	*current;

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
	//free_cmd2(path);
	return (final_path);
}

char	*find_cmd(t_env *env, char *cmd)
{
	char	*path;
	char	**tab_path;
	char	*final_path;

	path = find_path(env);
	tab_path = ft_split(path, ':');
	if (!tab_path)
		return (NULL);
	final_path = right_path(tab_path, cmd);
	free_cmd2(tab_path);
	return (final_path);
}

char	*init_path(t_ast **ast, t_env *env)
{
	char	*path;

	path = find_cmd(env, (*ast)->cmd2[0]);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, (*ast)->cmd2[0], ft_strlen((*ast)->cmd2[0]));
		write(2, ": command not found\n", 21);
		return (NULL);
	}
	return (path);
}
