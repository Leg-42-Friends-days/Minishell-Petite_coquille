/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_len2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:01:42 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:21:12 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_split_word(char **split)
{
	int	j;
	int	word;

	j = 0;
	word = 0;
	while (split[j])
	{
		if (split[j][0] != '\0')
			word++;
		j++;
	}
	return (word);
}

int	add_len(t_sub_token *sub, int word)
{
	int	i;

	i = 0;
	if (word > 1)
		i += (word - 1);
	if (word > 1 && sub->prev && (sub->prev->quote == DOUBLE
			|| sub->prev->quote == SINGLE))
		i++;
	return (i);
}

int	len_cmd(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	if (!str || !*str)
		return (count);
	while (str[i])
	{
		if (str[i][j] != '\0')
			count++;
		i++;
	}
	return (count);
}

int	expand_len(t_ast *ast)
{
	int			i;
	t_token		*token;
	t_sub_token	*sub_token;

	i = 0;
	token = ast->cmd_token;
	while (token != NULL && token->type == WORD)
	{
		sub_token = token->sub_token;
		while (sub_token != NULL)
		{
			if (sub_token->quote == DOUBLE)
				i++;
			else if (sub_token->quote == NORMAL)
				i++;
			else if (sub_token->quote == SINGLE)
				i++;
			sub_token = sub_token->next;
		}
		token = token->next;
	}
	return (i);
}
