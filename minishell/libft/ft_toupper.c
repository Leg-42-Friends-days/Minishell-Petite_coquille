/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:09:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 11:09:35 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
/* 
#include <stdio.h>
#include <ctype.h>

int	ft_toupper(int c);

int	main(void)
{
	int	c;

	c = 52;
	printf("petit : %c\n", c);
	printf("grand : %c", ft_toupper(c));
} */