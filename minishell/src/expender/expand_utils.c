/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:10:19 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:12:07 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_null(char *str)
{
	if (!str)
		return (NULL);
	if (str[0] == '\0')
		return (free(str), NULL);
	return (str);
}

bool	check_dollars(t_sub_token *current_sub)
{
	if (current_sub->quote == NORMAL && ft_strncmp(current_sub->var, "$",
			-1) == 0 && current_sub->next && (current_sub->next->quote == DOUBLE
			|| current_sub->next->quote == SINGLE))
		return (true);
	return (false);
}

bool	check_if_empty(char **split, int i)
{
	i++;
	while (split[i])
	{
		if (split[i][0] != '\0')
			return (true);
		i++;
	}
	return (false);
}

char	*strjoin_exp(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s1)
		free(s1);
	return (str[i + j] = '\0', str);
}

char	*call_join(char **str)
{
	int		i;
	char	*full_string;

	i = 0;
	if (!str || !*str)
		return (NULL);
	full_string = NULL;
	while (str[i])
	{
		full_string = strjoin_exp(full_string, str[i]);
		if (!full_string)
			return (NULL);
		i++;
	}
	return (full_string);
}
