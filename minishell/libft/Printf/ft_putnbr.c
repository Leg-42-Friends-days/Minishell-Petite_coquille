/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:34:45 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/25 19:29:53 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	*count = *count + 1;
}

static void	ft_write(int n, int *count)
{
	if (n >= 10)
		ft_write(n / 10, count);
	ft_putchar((n % 10) + '0', count);
}

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count = *count + 11;
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		*count = *count + 1;
		n = n / -1;
	}
	ft_write(n, count);
}
