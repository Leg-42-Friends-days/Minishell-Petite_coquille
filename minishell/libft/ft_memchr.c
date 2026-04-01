/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:04:37 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:05:31 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
/* 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n);

int	main(void)
{
	char	s[] = "bonjour a toi";

	printf("%s", (char *)ft_memchr(s, 'a', 9));
} */