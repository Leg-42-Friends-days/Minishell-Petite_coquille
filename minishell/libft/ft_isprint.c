/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:32:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/06 13:26:28 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/* 
#include <ctype.h>
#include <stdio.h>

int	ft_isprint(int c);

int	main(void)
{
	int	nb;

	nb = 126;
	printf("%d", ft_isprint(nb));
	printf("\nla vraie foncion %d", isprint(nb));
} */