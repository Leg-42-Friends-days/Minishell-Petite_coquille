/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:08:58 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:09:02 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
/* 
#include <stdio.h>
#include <ctype.h>

int	ft_tolower(int c);

int	main(void)
{
	int	c;

	c = 70;
	printf("grand : %c\n", c);
	printf("petit : %c", ft_tolower(c));
} */