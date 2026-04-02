/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:02:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/07 19:16:58 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((char *)(dest + i)) = *((char *)(src + i));
		i ++;
	}
	return (dest);
}
/* 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);

int	main(void)
{
	//char	dest[] = "hello toi";
	//char	src[] = "coucou toi";
	char	*s;
	int	n;

	n = 3;
	//printf("source de base :%s", src);
	//printf("\ndest avant :%s", dest);
	//ft_memcpy(src, src, n);
	s = memcpy(((void*)0), ((void*)0), n);
	printf("\ndest apres :%s", s);
} */