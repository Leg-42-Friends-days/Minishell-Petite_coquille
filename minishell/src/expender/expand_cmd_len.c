/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:59:11 by mickzhan          #+#    #+#             */
/*   Updated: 2026/03/31 18:32:45 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wildcard_len_add(void)
{
	int	len;

	len = wild_card_len();
	if (len > 1)
		return (len - 1);
	return (0);
}

int	add_normal_len(char **split)
{
	int	i;
	int	string;
	int	len;

	i = 0;
	string = 0;
	len = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
		{
			string++;
			if (check_if_wildcard(split[i]) == false)
				len += wildcard_len_add();
		}
		i++;
	}
	if (string > 1)
		len += (string - 1);
	return (len);
}

int	add_split_len(t_sub_token *sub, char *str)
{
	char	**split;
	int		len;
	int		word;

	len = 0;
	split = ft_split(str, ' ');
	if (!split)
		return (0);
	len += add_normal_len(split);
	word = count_split_word(split);
	if (word > 1 && sub->prev && (sub->prev->quote == DOUBLE
			|| sub->prev->quote == SINGLE))
		len++;
	free_split(split);
	return (len);
}

int	check_if_add(t_sub_token *sub, t_global *global)
{
	char	*str;
	int		len;

	len = 0;
	if (sub->quote != NORMAL)
		return (0);
	str = ft_strdup(sub->var);
	if (!str)
		return (0);
	str = app_expend(str, global, false);
	if (!str || str[0] == '\0')
		return (free(str), 0);
	if (ft_strchr(str, ' '))
		len += add_split_len(sub, str);
	else if (check_if_wildcard(str) == false)
		len += wildcard_len_add();
	return (free(str), len);
}

int	expand_len_token(t_ast *ast, t_global *global)
{
	int			i;
	t_token		*token;
	t_sub_token	*sub_tok;

	i = 0;
	token = ast->cmd_token;
	while (token != NULL && token->type == WORD)
	{
		i++;
		sub_tok = token->sub_token;
		while (sub_tok)
		{
			i += check_if_add(sub_tok, global);
			sub_tok = sub_tok->next;
		}
		token = token->next;
	}
	return (i);
}
