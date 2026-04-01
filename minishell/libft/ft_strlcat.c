/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:10:18 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:10:19 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	lend;
	size_t	i;
	size_t	n;

	lens = 0;
	lend = 0;
	while (src[lens] != '\0')
		lens++;
	while (dst[lend] != '\0' && lend < dstsize)
		lend++;
	if (lend == dstsize)
		return (lens + dstsize);
	i = lend;
	n = 0;
	while (dstsize > i + 1 && src[n] != '\0')
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	dst[i] = '\0';
	return (lens + lend);
}
/* 
#include <stdio.h>
#include <stddef.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

int	main(void)
{
	char	dst[25] = "caca ";
	char	src[] = "mais mdr";
	int	dstsize;
	int	N;

	dstsize = 25;
	N = ft_strlcat(dst, src, dstsize);
	printf("%d\n",N );
	printf("%s", dst);
} */