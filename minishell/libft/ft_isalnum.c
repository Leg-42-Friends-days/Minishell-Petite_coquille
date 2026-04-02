/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:32:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/06 13:05:33 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		return (c);
	return (0);
}
/* 
#include <ctype.h>
#include <stdio.h>

int	ft_isalnum(int c);

int	main(void)
{
	int	nb;

	nb = 5;
	printf("%d", ft_isalnum(nb));
	printf("\nla vraie foncion %d", isalnum(nb));
}
 */