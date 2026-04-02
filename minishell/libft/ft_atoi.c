/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:43:52 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/12/15 21:07:13 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	rslt;

	i = 0;
	sign = 1;
	rslt = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i] != '\0')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		rslt = rslt * 10 + (str[i] - '0');
		i++;
	}
	return (sign * rslt);
}
/* 
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *str);

int	main(void)
{
	char	str[] = ".  +23a4";

	printf("%d", ft_atoi(str));
} */