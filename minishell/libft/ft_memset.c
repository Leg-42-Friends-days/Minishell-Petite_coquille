/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:12:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/07 11:21:09 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
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
/* 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n);

int	main(void)
{
	char	str[] = "bonjour a toi";

	printf("avant : %s", str);
	ft_memset((str + 1), 65, (sizeof(char) * 3));
	//memset((str + 1), 65, (sizeof(char) * 3));
	printf("\napres ma fonction : %s", str);
	//printf("\n vraie fonction : %s", str);
} */