/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_wild2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:14:42 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:15:24 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_end(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '*')
		i++;
	while (str[i] == '*')
		i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

bool	start_compare(char *str, char *entry)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '*')
	{
		if (str[i] != entry[i])
			return (true);
		i++;
	}
	return (false);
}

bool	end_compare(char *str, char *entry)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(entry) - 1;
	if (j < i)
		return (true);
	while (i >= 0)
	{
		if (str[i] != entry[j])
			return (true);
		i--;
		j--;
	}
	return (false);
}

bool	check_side(char *str, char *entry)
{
	char	*start;
	char	*end;
	int		i;

	i = 0;
	start = ft_substr(str, 0, len_start(str));
	end = ft_substr(str, len_start_and_star(str), len_end(str));
	if (!start || !end)
		return (free(start), free(end), false);
	if (ft_strlen(start) + ft_strlen(end) > ft_strlen(entry))
		return (free(start), free(end), false);
	if (start_compare(start, entry) == false && end_compare(end,
			entry) == false)
		return (free(start), free(end), true);
	return (free(start), free(end), false);
}

bool	check_inside_len(char *str, char *entry)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = ft_strlen(entry);
	while (str[i])
	{
		if (str[i] != '*')
			count++;
		i++;
	}
	if (count > len)
		return (true);
	return (false);
}
