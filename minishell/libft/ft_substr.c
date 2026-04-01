/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:32:11 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 12:44:17 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_lenght(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rslt;
	size_t	i;
	size_t	lenlen;

	lenlen = 0;
	if (start > ft_lenght(s))
		start = ft_lenght(s);
	while (lenlen < (unsigned long)len && s[start] != '\0')
	{
		lenlen++;
		start++;
	}
	rslt = (char *)malloc((lenlen + 1) * sizeof(char));
	if (!rslt)
		return (NULL);
	i = 0;
	start = start - lenlen;
	while (i < (unsigned long)len && s[start] != '\0')
	{
		rslt[i] = s[start];
		i++;
		start++;
	}
	rslt[i] = '\0';
	return (rslt);
}
/* 
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	main(void)
{
	char	s[] = "hola";
	char	*rs;

	rs = ft_substr(s, 4294967295, 1844674407370955161);
	printf("%s", rs);
} */