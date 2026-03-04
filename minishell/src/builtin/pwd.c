/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:31:27 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/04 16:08:01 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **cmd, t_env *env)
{
	char	*pwd;

	(void)cmd;
	pwd = ft_getenv(env, "PWD");
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);

	return (0);
}
