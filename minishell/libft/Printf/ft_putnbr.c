/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:34:01 by mickzhan          #+#    #+#             */
/*   Updated: 2026/01/23 10:07:39 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_int(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb >= 10)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

int	ft_putnbr(int nb, int fd)
{
	int	len;

	len = len_int(nb);
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10, fd);
	ft_putchar(nb % 10 + '0', fd);
	return (len);
}

// int main()
// {
// 	ft_putnbr(-23);
// 	printf("\n%d", -23);
// }
