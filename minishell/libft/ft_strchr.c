/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:07:59 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:08:02 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	while (i <= len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		else
			i++;
	}
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c);

int	main(void)
{
	char s[] = "a la peche aux moules je ne veux pas aller maman";
	int	c;

	c = 'a';
	printf("%s", ft_strchr(s, c));
} */