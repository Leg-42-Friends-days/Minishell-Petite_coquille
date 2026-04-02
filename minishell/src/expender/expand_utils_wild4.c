/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_wild4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:19:05 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/02 19:12:24 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_all_dir(t_ast *ast, int start)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = start;
	dp = opendir(".");
	if (!dp)
		return (i);
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			i++;
		}
		entry = readdir(dp);
	}
	return (closedir(dp), i);
}

bool	mid_compare(char *str, char *entry)
{
	int	i;
	int	j;
	int	k;

	if (!entry || !str)
		return (true);
	i = 0;
	while (entry[i])
	{
		j = 0;
		k = 0;
		while (entry[i + k] == str[j])
		{
			k++;
			j++;
			if (str[j] == '\0')
			{
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	check_inside(char *str, char *entry)
{
	if (check_inside_len(str, entry) == true)
		return (false);
	else if (check_inside_string(str, entry) == true)
		return (false);
	return (true);
}

bool	check_if_next_token_wild(t_sub_token *sub_to)
{
	if (sub_to->next && (sub_to->next->quote == DOUBLE
			|| sub_to->next->quote == SINGLE))
		return (false);
	else if (sub_to->prev && (sub_to->prev->quote == DOUBLE
			|| sub_to->prev->quote == SINGLE))
		return (false);
	return (true);
}

int	mid_add(char *str, char *entry)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (entry[i])
	{
		j = 0;
		k = 0;
		while (entry[i + k] == str[j])
		{
			k++;
			j++;
			if (str[j] == '\0')
				return (i);
		}
		i++;
	}
	return (i);
}
