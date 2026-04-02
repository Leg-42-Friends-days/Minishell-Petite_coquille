/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:02:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/07 19:24:21 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			*((unsigned char *)(dest + i)) = *((unsigned char *)(src + i));
			i++;
		}
		return (dest);
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			*((unsigned char *)(dest + i)) = *((unsigned char *)(src + i));
		}
		return (dest);
	}
}
/* 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n);

int	main(void)
{
	char	dest[100] = "Learningisfun";
	//char	src[] = "coucou toi";
	int	n;

	n = 13;
	//printf("source de base :%s", src);
	printf("\ndest avant :%s", dest);
	//ft_memmove(dest, src, n);
	ft_memmove((dest + 8), dest, n);
	printf("\ndest apres :%s", dest);
} */