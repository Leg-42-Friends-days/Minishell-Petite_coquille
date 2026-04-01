/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_wild3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:16:11 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:33:11 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_start(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

int	len_start_and_star(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '*')
		i++;
	while (str[i] == '*')
		i++;
	return (i);
}

bool	start_wildcard(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '*')
		return (true);
	return (false);
}

bool	end_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != '*')
		return (true);
	return (false);
}

int	last_index(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
