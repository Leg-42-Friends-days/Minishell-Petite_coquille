/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:18:07 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:18:47 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	inside_string(bool start, bool end, char **str, char *entry)
{
	int	i;
	int	len;

	i = 0;
	if (!str || !*str)
		return (false);
	len = last_index(str) - 1;
	while (str[i])
	{
		if (start_compare(str[0], entry) == true && start == true)
			return (false);
		else if (end_compare(str[len], entry) == true && end == true)
			return (false);
		else if (mid_compare(str[i], entry) == true)
			return (false);
		i++;
	}
	return (true);
}

bool	check_inside_string(char *str, char *entry)
{
	bool	start;
	bool	end;
	char	**tableau;

	start = start_wildcard(str);
	end = end_wildcard(str);
	tableau = ft_split(str, '*');
	if (inside_string(start, end, tableau, entry) == true)
		return (free_split(tableau), false);
	return (free_split(tableau), true);
}

int	call_wild_side(t_ast *ast, char *str, int index, bool checker)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = index;
	dp = opendir(".");
	if (!dp)
		return (i);
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false && check_side(str,
				entry->d_name) == true)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			checker = true;
			i++;
		}
		entry = readdir(dp);
	}
	if (checker == false)
		ast->cmd2[i++] = ft_strdup(str);
	return (closedir(dp), i);
}

int	call_wild_multi(t_ast *ast, char *str, int index, bool checker)
{
	struct dirent	*entry;
	DIR				*dp;
	int				i;

	i = index;
	dp = opendir(".");
	if (!dp)
		return (i);
	entry = readdir(dp);
	while (entry)
	{
		if (first_letter(entry->d_name) == false && check_inside(str,
				entry->d_name) == true)
		{
			ast->cmd2[i] = ft_strdup(entry->d_name);
			checker = true;
			i++;
		}
		entry = readdir(dp);
	}
	if (checker == false)
		ast->cmd2[i++] = ft_strdup(str);
	return (closedir(dp), i);
}

int	expand_wildcard(char *str, t_ast *ast, int *index)
{
	if (only_wildcard(str) == true)
		*index = call_all_dir(ast, *index);
	else if (check_if_star_alone(str) == 1)
		*index = call_wild_side(ast, str, *index, false);
	else if (check_if_star_alone(str) > 1)
		*index = call_wild_multi(ast, str, *index, false);
	return (*index);
}
