/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:27:52 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 20:12:08 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb20(int nb)
{
	int	nb20;

	nb20 = 1;
	while (nb >= 10)
	{
		nb20 = nb20 * 10;
		nb = nb / 10;
	}
	return (nb20);
}

static int	ft_leng(int nb)
{
	int	len;

	len = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static void	fr_convert(char *rslt, int n, int sign)
{
	char	chiffre;
	int		nb20;
	int		i;

	nb20 = ft_nb20(n);
	i = 0;
	if (sign >= 2)
	{
		rslt[0] = '-';
		i++;
		if (sign == 3)
		{
			rslt[1] = '2';
			i++;
		}
	}
	while (nb20 > 0)
	{
		chiffre = (n / nb20) + '0';
		rslt[i] = chiffre;
		n = n - ((chiffre - '0') * nb20);
		nb20 = nb20 / 10;
		i++;
	}
	rslt[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*rslt;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = 147483648;
			sign = 3;
		}
		else
		{
			n = n / -1;
			sign = 2;
		}
	}
	len = ft_leng(n);
	rslt = malloc((len + sign) * sizeof(char));
	if (!rslt)
		return (NULL);
	fr_convert(rslt, n, sign);
	return (rslt);
}
/* 
#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa(int n);

int	main(void)
{
	char	*str = ft_itoa(-2147483648);

	printf("%s", str);
	free(str);
}
 */