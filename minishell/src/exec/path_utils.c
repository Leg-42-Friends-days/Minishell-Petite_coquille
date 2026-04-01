/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:59:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/01 11:59:47 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_directory_first(char *cmd, int *error)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		*error = 3;
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		*error = 4;
		return (1);
	}
	*error = 0;
	return (0);
}

char	*is_directory_error(int *error, int *error_code, t_ast **ast)
{
	if (*error == 3)
	{
		perror("minishell");
		*error_code = 127;
	}
	if (*error == 4)
	{
		write(2, "minishell: ", 11);
		write(2, (*ast)->cmd2[0], ft_strlen((*ast)->cmd2[0]));
		write(2, ": Is a directory\n", 17);
		*error_code = 126;
	}
	if (*error == 5)
	{
		write(2, "minishell: .: filename argument required\n", 41);
		*error_code = 2;
	}
	*error = 0;
	return (NULL);
}
