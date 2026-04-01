/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:22:51 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/25 19:26:45 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_hexa(int c, int *count)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	write(1, hexa + c, 1);
	*count = *count + 1;
}

void	ft_lowerhexa(unsigned int n, int *count)
{
	if (n >= 16)
		ft_lowerhexa(n / 16, count);
	ft_putchar_hexa(n % 16, count);
}
