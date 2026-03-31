/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fonction2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:08:30 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:08:43 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_index(t_ast *ast, int *index)
{
	if (ast->cmd2[*index])
	{
		(*index)++;
		ast->cmd2[*index] = NULL;
	}
}

void	add_str_to_cmd(t_ast *ast, int *index, char *str)
{
	char	*new_str;

	if (!str)
		return ;
	if (!ast->cmd2[*index])
	{
		ast->cmd2[*index] = ft_strdup(str);
		return ;
	}
	new_str = ft_strjoin(ast->cmd2[*index], str);
	if (!new_str)
		return ;
	free(ast->cmd2[*index]);
	ast->cmd2[*index] = new_str;
}

char	*check_if_space(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			new_str[j++] = ' ';
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*normal_value(t_sub_token *sub, t_global *global)
{
	char	*tmp;
	char	*str;
	char	*new_str;

	tmp = ft_strdup(sub->var);
	if (!tmp)
		return (NULL);
	if (sub->next && (sub->next->quote == DOUBLE || sub->next->quote == SINGLE))
		tmp = remove_dollar(tmp);
	tmp = app_expend(tmp, global, false);
	tmp = remove_null(tmp);
	if (!tmp)
		return (NULL);
	str = ft_strtrim(tmp, " ");
	free(tmp);
	if (!str || str[0] == '\0')
		return (free(str), NULL);
	new_str = check_if_space(str);
	new_str = remove_null(new_str);
	return (new_str);
}

void	add_split_words(t_ast *ast, char **split, int *index)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
		{
			if (check_if_wildcard(split[i]) == false)
			{
				add_index(ast, index);
				*index = expand_wildcard(split[i], ast, index);
				ast->cmd2[*index] = NULL;
			}
			else
			{
				add_str_to_cmd(ast, index, split[i]);
				if (check_if_empty(split, i))
					add_index(ast, index);
			}
		}
		i++;
	}
}
