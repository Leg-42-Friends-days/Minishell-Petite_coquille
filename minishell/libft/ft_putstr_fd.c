/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:56:48 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 21:01:04 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/* 
#include <unistd.h>
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd);

int	main(void)
{
	char	s[] = "coucou salut";
	int	fd;

	fd = open("test.txt", O_RDWR);
	if (fd > 0)
		ft_putstr_fd(s, fd);
	else
		write(1, "erreur", 6);
} */