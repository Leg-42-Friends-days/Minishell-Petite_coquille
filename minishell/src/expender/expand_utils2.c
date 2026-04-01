/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:20:34 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:32:38 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_dollar(char *str)
{
	int		len;
	int		i;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '$')
	{
		new_str = malloc(sizeof(char) * len + 1);
		if (!new_str)
			return (str);
		i = 0;
		while (i < len - 1)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
		return (free(str), new_str);
	}
	return (str);
}

bool	check_dollar(char *str, int i)
{
	if (str[i] == '$' && !(str[i + 1] == ' ' || str[i + 1] == '\0') && str[i
			+ 1] != '"' && str[i + 1] != '/')
		return (true);
	return (false);
}
