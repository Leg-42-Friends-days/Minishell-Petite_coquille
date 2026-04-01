/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:35:53 by mickzhan          #+#    #+#             */
/*   Updated: 2026/01/23 09:52:03 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	len_unsigned_int(unsigned int nb)
{
	unsigned int	i;

	i = 1;
	while (nb >= 10)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

unsigned int	ft_unsigned_putnbr(unsigned int nb, int fd)
{
	int	len;

	len = len_unsigned_int(nb);
	if (nb >= 10)
		ft_putnbr(nb / 10, fd);
	ft_putchar(nb % 10 + '0', fd);
	return (len);
}

// int main()
// {
// 	ft_unsigned_putnbr(12141);
// }
