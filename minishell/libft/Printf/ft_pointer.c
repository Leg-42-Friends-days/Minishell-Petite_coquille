/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:37:45 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/25 19:27:26 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_hexa(unsigned long c, int *count)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	write(1, hexa + c, 1);
	*count = *count + 1;
}

static void	ft_conversion(const unsigned long n, int *count)
{
	if (n >= 16)
		ft_conversion(n / 16, count);
	ft_putchar_hexa(n % 16, count);
}

void	ft_pointer(void *n, int *count)
{
	if (!n)
	{
		write(1, "(nil)", 5);
		*count = *count + 5;
		return ;
	}
	write(1, "0x", 2);
	*count = *count + 2;
	ft_conversion((unsigned long) n, count);
}
