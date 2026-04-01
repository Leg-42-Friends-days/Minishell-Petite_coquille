/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:32:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/06 13:15:04 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/* 
#include <ctype.h>
#include <stdio.h>

int	ft_isascii(int c);

int	main(void)
{
	int	nb;

	nb = 128;
	printf("%d", ft_isascii(nb));
	printf("\nla vraie foncion %d", isascii(nb));
}
 */