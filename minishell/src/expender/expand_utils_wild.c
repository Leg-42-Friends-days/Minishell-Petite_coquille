/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_wild.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:13:01 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:13:40 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_if_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (false);
		i++;
	}
	return (true);
}

bool	only_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (false);
		i++;
	}
	return (true);
}

bool	first_letter(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '.')
		return (true);
	return (false);
}

int	wild_card_len(void)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = 0;
	dp = opendir(".");
	if (!dp)
		return (0);
	entry = readdir(dp);
	while (entry)
	{
		i++;
		entry = readdir(dp);
	}
	return (closedir(dp), i);
}

int	check_if_star_alone(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i] == '*')
		{
			i++;
			j++;
		}
		if (0 < j)
			count++;
		else
			i++;
	}
	return (count);
}
