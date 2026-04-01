/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:42:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/25 19:30:24 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *s, int *count)
{
	int	i;

	if (!s)
	{
		write(1, "(null)", 6);
		*count = *count + 6;
		return ;
	}
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		*count = *count + 1;
		i++;
	}
}
