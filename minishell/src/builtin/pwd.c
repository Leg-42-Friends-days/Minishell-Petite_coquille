/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:31:27 by mickzhan          #+#    #+#             */
/*   Updated: 2026/02/09 17:36:39 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

t_pwd	*current_directory_path(t_pwd *pwd)
{
	char	cdw[1024];
	int		i;

	i = ft_strlen(getcwd(cdw, sizeof(cdw)));
	if (i == 0)
		perror("getwcd");
	if (pwd->oldpwd && pwd->pwd)
	{
		free(pwd->oldpwd);
		pwd->pwd = getcwd(cdw, sizeof(cdw));
		pwd->oldpwd = pwd->pwd;
	}
	else
	{
		pwd->pwd = malloc(sizeof(char) * (i + 1));
		pwd->pwd = ft_strcpy(pwd->pwd, cdw);
		pwd->oldpwd = pwd->pwd;
	}
	return (pwd);
}
