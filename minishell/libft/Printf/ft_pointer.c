/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:40:37 by mickzhan          #+#    #+#             */
/*   Updated: 2026/01/23 10:09:53 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	pointer_converter(unsigned long nb, int fd)
{
	unsigned long	len;
	unsigned long	i;
	unsigned long	*tmp;

	i = 0;
	len = ft_div_intlen(nb);
	tmp = malloc(sizeof(long) * len);
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

int	ft_pointer(void *p, int fd)
{
	unsigned long	conv;
	int				count;

	count = 2;
	conv = (unsigned long)p;
	if (!p)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	count += pointer_converter(conv, fd);
	return (count);
}

// int	main(void)
// {
//     int nb = 1;
//     int *p = &nb;
//     printf("%p\n", p);
//     // printf("%p\n", p);
//     // printf("%d", *(int *)p);
// 	ft_pointer(p);
// }