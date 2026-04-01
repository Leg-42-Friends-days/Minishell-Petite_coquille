/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:24:24 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 12:11:28 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memoset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	s = str;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*rslt;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(0));
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	rslt = malloc(nmemb * size);
	if (!rslt)
		return (NULL);
	ft_memoset(rslt, 0, (nmemb * size));
	return (rslt);
}
/* 
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size);

int	main(void)
{
	char	*ptr;
	int	nmemb;
	int	i;

	nmemb = 4;
	ptr = ft_calloc(nmemb, 1);
	i = 0;
	while (i < nmemb)
	{
		printf("%d", (char)ptr[i]);
		i++;
	}
} */