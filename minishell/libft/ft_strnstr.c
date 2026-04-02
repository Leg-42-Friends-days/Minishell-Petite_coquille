/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:01:31 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:03:00 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)haystack;
	if (needle[0] == '\0')
		return (str);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (str[i + j] == needle[j] && (i + j) < len
			&& needle[j] != '\0' && str[i + j] != '\0')
		{
			j++;
		}
		if (needle[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (0);
}
/* 
#include <string.h>
#include <stddef.h>
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int	main(void)
{
	char	haystack[] = "coucou la compagnie, ca va ou quoi";
	char	needle[] = "";

	printf("%s", ft_strnstr(haystack, needle, 25));
} */