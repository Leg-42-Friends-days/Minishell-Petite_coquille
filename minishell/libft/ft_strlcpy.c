/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:11:16 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:11:18 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (src[n] != '\0')
		n++;
	if (dstsize == 0)
		return (n);
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (n);
}
/* 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int	main(void)
{
	char	dst[13];
	char	src[] = "bonjour a toi";
	int	n;

	n = 13;
	ft_strlcpy(dst, src, n);
	printf("%s", dst);
} */