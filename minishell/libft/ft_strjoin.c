/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:50:48 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 13:54:04 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_fil(char const *s1, char const *s2, char *rslt)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rslt;
	int		ls1;
	int		ls2;

	ls1 = ft_strl((char *)s1);
	ls2 = ft_strl((char *)s2);
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
/* 
#include <stdlib.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2);

int	main(void)
{
	char	s1[] = "coucou";
	char	s2[] = " toi";
	char	*rslt;

	rslt = ft_strjoin(s1, s2);
	printf("%s", rslt);
} */