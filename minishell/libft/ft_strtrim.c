/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:00:51 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 16:43:02 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (s1[i] == set[j])
			return (1);
		j++;
	}
	return (0);
}

static int	ft_bgn(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_isset(s1, set, i) && s1[i] != '\0')
		i++;
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	len--;
	while (ft_isset(s1, set, len) && len >= 0)
	{
		len--;
		i++;
	}
	return (i);
}

static char	*ft_filll(char const *s1, char *rslt, int size, int ibgn)
{
	int	i;

	i = 0;
	while (i < size)
	{
		rslt[i] = s1[ibgn];
		i++;
		ibgn++;
	}
	rslt[i] = '\0';
	return (rslt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ibgn;
	int		iend;
	int		len;
	int		size;
	char	*rslt;

	if (!s1 || !set)
		return (NULL);
	ibgn = ft_bgn(s1, set);
	iend = ft_end(s1, set);
	len = 0;
	while (s1[len] != '\0')
		len++;
	size = (len - ibgn - iend);
	if (size < 0)
		size = 0;
	rslt = (char *)malloc((size + 1) * sizeof(char));
	if (!rslt)
		return (NULL);
	return (ft_filll(s1, rslt, size, ibgn));
}
/* 
#include <stdio.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set);

int	main(void)
{
 	char	s1[] = "**test**";
 	char	set[] = "t*";
 	char	*rslt;

	rslt = ft_strtrim(s1, set);
	printf("%s", rslt);
} */