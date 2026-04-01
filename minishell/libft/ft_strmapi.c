/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:15:28 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 20:34:37 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* 
#include <stdlib.h>
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	ft_change(unsigned int index, char c)
{
	(void)index;
	return (c + 1);
}

int	main(void)
{
	char	*s;
	char	*str;

	s = "bonjour";
	printf("avant : %s\n", s);
	str = ft_strmapi(s, ft_change);
	printf("apres : %s", str);
	free(str);
} */