/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baseupper16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:11:18 by mickzhan          #+#    #+#             */
/*   Updated: 2026/01/23 11:00:33 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_div_intlen(size_t nb)
// {
// 	size_t	i;

// 	i = 0;
// 	while (nb)
// 	{
// 		nb /= 16;
// 		i++;
// 	}
// 	return (i);
// }

void	base_write16maj(unsigned int nb, int fd)
{
	if (nb == 0)
		ft_putchar(nb + '0', fd);
	if (nb >= 1 && nb <= 9)
		ft_putchar(nb + '0', fd);
	if (nb == 10)
		write(fd, "A", 1);
	if (nb == 11)
		write(fd, "B", 1);
	if (nb == 12)
		write(fd, "C", 1);
	if (nb == 13)
		write(fd, "D", 1);
	if (nb == 14)
		write(fd, "E", 1);
	if (nb == 15)
		write(fd, "F", 1);
}

unsigned int	ft_baseupper16(unsigned int nb, int fd)
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
		base_write16maj(tmp[i], fd);
		i--;
	}
	free(tmp);
	return (len);
}

// int	main(void)
// {
// 	ft_baseupper16(189471241);
// 	printf("\n%x", 189471241);
// }
