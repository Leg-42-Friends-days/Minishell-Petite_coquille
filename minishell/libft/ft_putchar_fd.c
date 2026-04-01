/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 20:55:08 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/* 
#include <unistd.h>
#include <fcntl.h>

void	ft_putchar_fd(char c, int fd);

int	main(void)
{
	int	fd;
	char	c;

	c = 'a';
	fd = open("test.txt", O_RDWR);
	if (fd > 0)
		ft_putchar_fd(c, fd);
	else
		write(1, "erreur", 6);
} */