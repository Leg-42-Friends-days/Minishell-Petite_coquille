/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:08:19 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/04 16:31:46 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (0);
	while (s1[i] && s2[i] && i < (size - 1) && (s1[i] == s2[i]))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char) s2[i]);
}

// int main()
// {
//     char *str = "Hello ";
//     char *str2 = "HelloR";
//     int size = 5;

//     printf("%d", ft_strncmp(str, str2, size));
// }
