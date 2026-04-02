/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:44:19 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/01/14 14:41:10 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_strlenn(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_fil(char const *s1, char const *s2, char *rslt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		rslt[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		rslt[i] = s2[j];
		i++;
		j++;
	}
	rslt[i] = '\0';
	return (rslt);
}

char	*ft_strjoinn(char const *s1, char const *s2)
{
	char	*rslt;
	int		ls1;
	int		ls2;

	ls1 = ft_strlenn((char *)s1);
	ls2 = ft_strlenn((char *)s2);
	if ((ls1 + ls2) == 0)
	{
		rslt = (char *)malloc(1 * sizeof(char));
		if (!rslt)
			return (NULL);
		rslt[0] = '\0';
		return (rslt);
	}
	rslt = (char *)malloc((ls1 + ls2 + 1) * sizeof(char));
	if (! rslt)
		return (NULL);
	return (ft_fil(s1, s2, rslt));
}

int	ft_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	char	*rslt;
	size_t	i;
	size_t	lenlen;

	lenlen = 0;
	if (start > ft_strlenn(s))
		start = ft_strlenn(s);
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
