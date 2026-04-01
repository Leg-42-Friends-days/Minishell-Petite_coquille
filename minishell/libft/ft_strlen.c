/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:40:09 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/06 13:50:09 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
/* 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

size_t	ft_strlen(const char *s);

int	main(void)
{
	char	*str;

	str = "j";
	printf("%lu", ft_strlen(str));
	printf("\nla vraie fonction %lu", strlen(str));
} */