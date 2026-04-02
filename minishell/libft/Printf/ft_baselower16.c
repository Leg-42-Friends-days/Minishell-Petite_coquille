/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselower16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:42:38 by mickzhan          #+#    #+#             */
/*   Updated: 2026/01/23 09:52:51 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_div_intlen(unsigned long nb)
{
	unsigned int	i;

	i = 1;
	while (nb >= 16)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

void	base_write16(unsigned int nb, int fd)
{
	if (nb == 0)
		ft_putchar(nb + '0', fd);
	if (nb >= 1 && nb <= 9)
		ft_putchar(nb + '0', fd);
	if (nb == 10)
		write(fd, "a", 1);
	if (nb == 11)
		write(fd, "b", 1);
	if (nb == 12)
		write(fd, "c", 1);
	if (nb == 13)
		write(fd, "d", 1);
	if (nb == 14)
		write(fd, "e", 1);
	if (nb == 15)
		write(fd, "f", 1);
}

unsigned int	ft_baselower16(unsigned int nb, int fd)
{
	unsigned int	len;
	unsigned int	i;
	unsigned int	*tmp;

	i = 0;
	len = ft_div_intlen(nb);
	tmp = malloc(sizeof(int) * len);
	if (!tmp)
		return (0);
	while (i < len)
	{
		tmp[i] = nb % 16;
		nb /= 16;
		i++;
	}
	i--;
	while (i + 1 != 0)
	{
		base_write16(tmp[i], fd);
		i--;
	}
	free(tmp);
	return (len);
}

// int	main(void)
// {
// 	ft_baselower16(2131421421);
// }