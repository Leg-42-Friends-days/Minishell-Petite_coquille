/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:44:49 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 18:59:36 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmptwords(char const *s, char c)
{
	int	i;
	int	cmpt;

	i = 0;
	cmpt = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			cmpt++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (cmpt);
}

static void	ft_free(char **rslt, int j)
{
	while (j >= 0)
	{
		free(rslt[j]);
		j--;
	}
	free(rslt);
}

static int	ft_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**ft_setmem(char **rslt, char const *s, int nbstr, char c)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0' && j < nbstr)
		{
			len = ft_len(&s[i], c);
			rslt[j] = ft_substr(s, i, len);
			if (!rslt[j])
				return (ft_free(rslt, j), NULL);
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	rslt[j] = NULL;
	return (rslt);
}

char	**ft_split(char const *s, char c)
{
	int		nbstr;
	char	**rslt;

	nbstr = ft_cmptwords(s, c);
	rslt = malloc((nbstr + 1) * sizeof(char *));
	if (!rslt)
		return (NULL);
	rslt = ft_setmem(rslt, s, nbstr, c);
	if (rslt == NULL)
		return (NULL);
	return (rslt);
}
/* 
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);

int	main(void)
{
	char	s[] = "hello! coucou";
	char	c;
	char	**rslt;
	int	i;

	c = 32;
	i = 0;
	rslt = ft_split(s, c);
	while (rslt[i] != NULL)
	{
		printf("%s\n", rslt[i]);
		free(rslt[i]);
		i++;
	}
	free(rslt[i]);
	free(rslt);
} */