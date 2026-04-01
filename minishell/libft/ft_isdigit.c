/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:32:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/06 11:53:49 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}
/* 
#include <ctype.h>
#include <stdio.h>

int	ft_isdigit(int c);

int	main(void)
{
	int	nb;

	nb = 60;
	printf("%d", ft_isdigit(nb));
	printf("\nla vraie foncion %d", isdigit(nb));
} */