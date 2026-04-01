/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:12:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/07 17:30:19 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)(s + i)) = '\0';
		i++;
	}
}
/* 
#include <strings.h>
#include <stdio.h>
#include <stddef.h>

void	ft_bzero(void *s, size_t n);

int	main(void)
{
	char	str[] = "bonjour a toi";

	printf("avant : %s", str);
	ft_bzero((str + 6), (sizeof(char) * 3));
	//bzero((str + 6), (sizeof(char) * 3));
	printf("\napres ma fonction : %s", str);
	printf("\n%si", &str[5]);
	//printf("\n vraie fonction : %s", str);
} */