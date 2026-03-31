/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:14:15 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/03/31 18:33:25 by ibrouin-         ###   ########.fr       */
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
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, path, 4))
			return (current->content);
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

int	is_directory_first(char *path, int *error)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		perror("minishell");
		*error = 127;
		//return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		write(1, "minishell: ", 11);
		write(1, path, ft_strlen(path));
		write(1, ": Is a directory\n", 17);
		//free(path);
		*error = 126;
		//return (126);
	}
	*error = 0;
	return (0);
}

char	*right_path(char **path, char *cmd, int *error)
{
	char	*cmdd;
	char	*final_path;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0)
		{
			if (is_directory(cmd, error))
				return (NULL);
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			*error = 2;
			return (NULL);
		}
		*error = 1;
		return (NULL);
	}
	cmdd = ft_strjoin("/", cmd);
	if (!cmdd)
		return (NULL);
	final_path = browse(path, cmdd);
	if (!final_path)
		return (NULL);
	return (final_path);
}

char	*find_cmd(t_env *env, char *cmd, int *error)
{
	char	*path;
	char	**tab_path;
	char	*final_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	path = find_path(env);
	if (!path)
		*error = 1;
	tab_path = ft_split(path, ':');
	if (!tab_path)
		return (NULL);
	final_path = right_path(tab_path, cmd, error);
	free_cmd2(tab_path);
	return (final_path);
}

char	*init_path(t_ast **ast, t_env *env, int *error)
{
	char	*path;

	*error = 127;
	path = find_cmd(env, (*ast)->cmd2[0], error);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, (*ast)->cmd2[0], ft_strlen((*ast)->cmd2[0]));
		if (*error == 0)
			write(2, ": command not found\n", 21);
		if (*error == 1)
			write(2, ": No such file or directory\n", 28);
		if (*error == 2)
		{
			write(2, ": Permission denied\n", 20);
			*error = 126;
		}
		if (*error == 3)
			is ()

		return (NULL);
	}
	return (path);
}
