/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:13:33 by ibrouin-          #+#    #+#             */
/*   Updated: 2025/11/10 12:28:48 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*dup;

	len = 0;
	while (s[len] != '\0')
		len++;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/* 
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s);

int	main(void)
{
	char	s[] = "coucou a toi";
	char	*str;

	str = ft_strdup(s);
	printf("%s", str);
}
 */