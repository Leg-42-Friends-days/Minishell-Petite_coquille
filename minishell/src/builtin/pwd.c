/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:31:27 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/30 11:52:08 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (cmd[i] != NULL)
	{
		if (cmd[i][j] == '-')
		{
			j++;
			if (cmd[i][j] && (cmd[i][j] == '-'
				|| (cmd[i][j] >= 'a' && cmd[i][j] <= 'z' )))
			{
				if (cmd[i][j] >= 'a' && cmd[i][j] <= 'z' )
					return (1);
			}
			j++;
			if (cmd[i][j] && (cmd[i][j] == '-'
				|| (cmd[i][j] >= 'a' && cmd[i][j] <= 'z' )))
				return (1);
		}
	}
	return (0);
}

int	ft_pwd(char **cmd, t_env *env)
{
	char	*pwd;

	(void)cmd;
	(void)env;
	if (is_option(cmd) == 1)
	{
		write(2, "minishell: pwd: -", 17);
		write(2, &cmd[1][1], 1);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}
