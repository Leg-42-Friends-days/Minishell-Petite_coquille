/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:35:52 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/12 20:46:21 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/* 
#include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

void	ft_change(unsigned int index, char *s)
{
	(void)index;
	*s = *s + 1;
}

int	main(void)
{
	char	s[] = "coucou toi";

	printf("avant : %s\n", s);
	ft_striteri(s, ft_change);
	printf("apres : %s\n", s);
} */