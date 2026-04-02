/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:07:12 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:07:13 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	i = len;
	while (i <= len && i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		else
			i--;
	}
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c);

int	main(void)
{
	char s[] = "teste";
	int	c;

	c = 'x';
	printf("%s", ft_strrchr(s, c));
} */