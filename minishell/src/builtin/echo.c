/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:26:08 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/23 19:16:55 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 92)
			write(1, &str[i], 1);
		i++;
	}
}

void	print_string_tab(char **cmd, t_env *env)
{
	int	i;
	char	*home;

	i = 0;
	home = ft_getenv(env, "HOME");
	while (cmd[i] != NULL)
	{
		if (i != 0)
			write (1, " ", 1);
		if (ft_strncmp(cmd[i], "~", 2) == 0)
			write (1, home, ft_strlen(home));
		else
			print_string(cmd[i]);
		i++;
	}
	write(1, "\n", 1);
}

void	print_with_option(char **cmd, t_env *env)
{
	int		i;
	char	*home;

	i = 0;
	home = ft_getenv(env, "HOME");
	while (cmd[i] != NULL)
	{
		if (i != 0)
			write (1, " ", 1);
		if (ft_strncmp(cmd[i], "~", 2) == 0)
			write (1, home, ft_strlen(home));
		else
			print_string(cmd[i]);
		i++;
	}
}

int	option_echo(char **cmd)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	j = 0;
	count = 1;
	while (cmd[i] != NULL)
	{
		if (cmd[i][j] == '-')
		{
			j++;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] == '\0')
				count ++;
			else
				break ;
			j = 0;
		}
		else
			break ;
		i++;
	}
	return (count);
}

int	ft_echo(char **cmd, t_env *env)
{
	int	option;

	if (cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	option = option_echo(cmd);
	if (option == 1)
		print_string_tab(&cmd[1], env);
	else
		print_with_option(&cmd[option], env);
	return (0);
}
