/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:59 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/20 14:33:07 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ft_atol(const char *str)
{
	int			i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (res >= (922337203685477580) && sign == 1 && str[i] > '7')
			return (0);
		if (res >= (922337203685477580) && sign == -1 && str[i] > '8')
			return (0);
		res = (str[i] - '0') + res * 10;
		i++;
	}
	return (1);
}

int	ft_atol(const char *str)
{
	int			i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + res * 10;
		i++;
	}
	return (res * sign);
}

int	is_not_numeric(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	if (cmd[i] == '\0')
		return (1);
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			break ;
		i++;
	}
	if (cmd[i] == '\0')
	{
		if (!check_ft_atol(cmd))
			return (1);
		else
			return (0);
	}
	else
		return (1);
}

int	ft_exit(char **cmd, t_env *env, int *error_code)
{
	(void)env;
	write(1, "exit\n", 5);
	if (!cmd[1])
		exit((*error_code) % 256);
	else
	{
		if (is_not_numeric(cmd[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, ": numeric argument required\n", 28);
			exit(2);
		}
	}
	if (cmd[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	else
		exit((ft_atol(cmd[1])) % 256);
	return (0);
}
