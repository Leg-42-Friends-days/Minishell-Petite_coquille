/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:32:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/06 11:43:42 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (c);
	return (0);
}
/* 
#include <ctype.h>
#include <stdio.h>

int	ft_isalpha(int c);

int	main(void)
{
	int	nb;

	nb = 66;
	printf("%d", ft_isalpha(nb));
	printf("\nla vraie foncion %d", isalpha(nb));
} */