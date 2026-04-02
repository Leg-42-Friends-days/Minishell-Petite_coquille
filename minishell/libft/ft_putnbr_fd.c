/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:06:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 22:08:51 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_fd(int n, int fd)
{
	if (n >= 10)
		ft_write_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n / -1;
	}
	ft_write_fd(n, fd);
}
/* 
#include <unistd.h>
#include <fcntl.h>

void	ft_putnbr_fd(int n, int fd);

int	main(void)
{
	int	fd;
	int	n;

	n = -2147483648;
	fd = open("test.txt", O_RDWR);
	if (fd > 0)
		ft_putnbr_fd(n, fd);
	else
		write(1, "erreur", 6);
} */